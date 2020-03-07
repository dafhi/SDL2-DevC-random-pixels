/*  -- Dev-C++     -lmingw32 -lSDL2main -lSDL2

    progressive pixel class and SDL2 encapsulation defines
    2020 Mar 5 - by dafhi
    
*/

#ifndef SDL2_AND_PROGR_H
#define SDL2_AND_PROGR_H

#include "propix.h"

//#define show_raytrace_importance_map

bool save_bmp = false; // save render

// ---------- framebuffer

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
float       rad, activ_max;

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
            rad = sqrt(gw * gw + gh * gh) / 35;\
        }\

#define let_OS_breathe(input_1, upd_modu)\
        if (input_1 % upd_modu == 0) {\
            auto k = SDL_UpdateWindowSurface(window);\
            if (rnd < .25) SDL_Delay(1);\
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
        
#ifdef show_raytrace_importance_map

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

void propix_frame(int frame, bool scaled = false, bool gamma = false, int update_mod = 1) {
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

#endif // --- ProgressivePixel_H
