/*  -- Dev-C++     -lmingw32 -lSDL2main -lSDL2

    progressive pixel class and SDL2 encapsulation defines
    2020 Mar 5 - by dafhi
    
*/

#ifndef SDL2_AND_PROGR_H
#define SDL2_AND_PROGR_H

#include "propix.h"

//#define show_importance_map

bool save_bmp = false;

#include <sdl.h>

SDL_Window  *window;
SDL_Surface *buf, *surf, *gsurf;
SDL_Event   event;
SDL_Rect    rdes, rsrc;

propix      *sum;
uint        *p32;
int         gw, wm;
int         gh, hm;
int         pitchBy, pitch_corner;
int         update_modulus = 3;
bool        quit = false;
bool        bool_initialize_profield = true;
bool        bool_gamma = false;
int         desi, srci;
float       g_rad;

void get_pointers(SDL_Surface* srf) {
    gsurf = srf;
}

void propix_fill( SDL_Surface* srf, vec3 col, double alpha = 1 ) {
    auto color = propix(col*alpha, alpha);
    get_pointers(srf);
    for (int j = hm; j >= 0; --j) {
        int jj = j * pitchBy;
        for (int i = jj; i < gw + jj; ++i) {
            sum[i] = color;
        }
    }
}

#define descriptors\
            pitchBy = gsurf->pitch / 4;\
            gw = gsurf->w;  wm = gw - 1;\
            gh = gsurf->h;  hm = gh - 1;\
            pitch_corner = pitchBy * hm;

void create_surface(int ww, int hh){
    if (surf != 0) return;
    surf = SDL_CreateRGBSurface(0, ww,hh, 32, 0, 0, 0, 0);
    get_pointers(surf);
    descriptors
    rsrc.w = surf->w;
}

void create_window(int w, int h){
    window = SDL_CreateWindow("SDL2 Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, 0);
    buf = SDL_GetWindowSurface(window);
    rsrc.h = 1;
    get_pointers(buf);
    descriptors
    rdes.w = buf->w;
}

#define invert_y_p32_sum(yy)\
        rsrc.y = hm-yy;\
        desi = (rsrc.y) * pitchBy;\
        srci = pitch_corner - desi;

#define initialize_profield\
        if (bool_initialize_profield) {\
            descriptors\
            p32 = (uint *)gsurf->pixels;\
            sum = new propix[pitchBy * gh];\
            bool_initialize_profield = false;\
            propix_fill(gsurf, vec3(0,0,0), .001);\
            g_rad = sqrt(gw * gw + gh * gh) / 90;\
        }\

#define let_OS_breathe(input_1, upd_modu)\
        if (input_1 % upd_modu == 0) {\
            auto k = SDL_UpdateWindowSurface(window);\
            if (rnd < 1) SDL_Delay(1);\
            SDL_PollEvent(&event);\
            switch (event.type) {\
                case SDL_QUIT:\
                quit = true;\
                case SDL_KEYDOWN:\
                switch( event.key.keysym.sym ) {\
                    case SDLK_ESCAPE:\
                    quit = true;\
                }\
            }\
        }\
        
#ifdef show_importance_map

    #define pixel_activity(gamma_or_no)\
                    float c = sum[srci+i].imap;\
                    p32[desi+i] = rgb_f(c,c,c);
#else

    #define pixel_activity(gamma_or_no)\
                    p32[desi+i] = sum[srci+i]gamma_or_no;
#endif

void scanline(const int j, const bool gamma = false){
        invert_y_p32_sum(j)
        static uint temp;
        if (gamma) {
            for (int i = 0; i < gw; ++i) {
                pixel_activity(.gamma())
            }
        } else {
            for (int i = 0; i < gw; ++i) {
                pixel_activity()
            }
        }
}

void show_render(bool scaled = false, bool gamma = false, int frame = 0, int update_mod = 1) {
    for (int j = 0; j < gh; j++) {
        scanline(j, gamma);
    }
    if (gsurf != buf & (frame % update_mod == 0)) {
        rsrc.y = 0; rsrc.h = gh;
        rdes.w = scaled ? buf->w : gw;
        rdes.h = scaled ? buf->h : gh;
        rdes.y = 0;
        SDL_BlitScaled(gsurf, &rsrc, buf, &rdes);
    }
    let_OS_breathe(frame, update_mod)
}

#define even_more_framebu___you_get_the_point(yy,upd_modu,bool_gamma)\
        \
        scanline(yy,bool_gamma);\
        \
        if (gsurf != buf) {\
            rdes.y = rsrc.y;\
            rsrc.h = 1;\
            rdes.h = 1;\
            rdes.w = rsrc.w;\
            SDL_BlitScaled(gsurf, &rsrc, buf, &rdes);\
        }\
        let_OS_breathe(yy,upd_modu)\
        \
        if (quit) break;

#define all_black (found_some_color = 0)

#define final_framebuff_stuff(delay)\
    std::cerr << "\nDone.\n";\
    SDL_UpdateWindowSurface(window);\
    if (!all_black && save_bmp) {\
      SDL_SaveBMP(gsurf, "output.bmp");\
    }\
    \
    SDL_Delay(delay);\
    SDL_FreeSurface(surf);\
    SDL_DestroyWindow(window);\
    SDL_Quit();

#define framebuffer_scanline(yy)\
        initialize_profield\
        invert_y_p32_sum(yy)

int found_some_color; // no .bmp if all black

inline void write_pixel(const vec3 color, const int idx, const int samps = 1) {
    sum[idx + srci] += propix(color, samps);
//    found_some_color += sum[idx + srci] != 0;  // no .bmp if all black
}

//        std::cout << sum[_idx].iter << " " << "" << "\n";
    //std::cout << SDL_GetError();
//            std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;

namespace aadot {

    void draw(float x, float y, propix col = vec3(1,1,1), const float rad=5, float slope=1) {
        static float salpha;

        /* slope = 1 .. 1 pixel aa edge
           slope = 2 .. 1/2 pixel (sharp)
           slope = 1/rad .. max blur
           slope < 1/rad .. rendering artifact */

        //salpha = 1 / rad;                         // clamp prevents artifact
        //slope = slope < salpha ? salpha : slope;  //

        y -= .5;
        int y0 = ffmax(y-rad, 0);
        int y1 = ffmin(y+rad+.5, hm);

        x -= .5;
        int x0 = ffmax(x-rad, 0);
        int x1 = ffmin(x+rad+.5, wm);

        float dy = (y0-y)*slope;
        const float dxleft = (x0-x)*slope;

        const float cone_h = slope*(rad+.25);     // +.25 is halfway between cone tip and pixel edge.  height average basically
        const float coneSq = cone_h*cone_h;      //avoid sqr() at blit corners
        const float sq = (cone_h-1)*(cone_h-1);  //avoid sqr() in dot center at max brightness.  don't remember why i made it cone_h-1

        for (int j = y0; j <= y1; j++) {
            float dx = dxleft;
            const float dySq = dy*dy;
            for (int i = x0 + j*pitchBy; i <= x1 + j*pitchBy; i++) {
                float salpha = dx*dx+dySq;
                if (salpha<sq) {

                    sum[i] += propix(col*col.iter, col.iter);
                } else if ( salpha <= coneSq) {

                    salpha = col.iter * (cone_h-sqrt(salpha));
                    sum[i] += propix(col * salpha, salpha);
                }
                dx+=slope;
            }
            dy+=slope;
        }

    }

    float relative_slope(float in, float radius) {
        return in / radius;
    }

}

#endif // --- ProgressivePixel_H
