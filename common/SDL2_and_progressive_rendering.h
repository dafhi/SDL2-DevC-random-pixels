/*  -- Dev-C++     -lmingw32 -lSDL2main -lSDL2

    progressive pixel class and SDL2 encapsulation defines
    2020 Feb 26 - by dafhi
    
*/

#ifndef ProgressivePixel_H
#define ProgressivePixel_H

#include "ray.h"

bool save_bmp = false; // save render

    #define propix progressive_pixel

class progressive_pixel {
      public:
          
    propix(tReal x=0, tReal y=0, tReal z=0, tReal w=0) { v=vec3(x,y,z); iter = w;}
    propix(const vec3& q, tReal w=1) {v = q; iter = w;}
    propix(const propix& q, tReal w=1) {v = q.v; iter = w;}

    operator vec3() { return v / iter; }
    const tReal operator[](int i) const { return v[i]; }

    operator uint() const { const tReal r = 1/iter; return rgb_i(v[0]*r, v[1]*r, v[2]*r); }
    uint sqr() const { const tReal r = 1/iter; return rgb_f(v[0]*r, v[1]*r, v[2]*r); }
    
    propix& operator+=(const propix &u) {
        v += u.v;
        iter += u.iter;
        return *this;
    }

    vec3  v;
    tReal iter;
};


inline std::ostream& operator<<(std::ostream &out, const propix &v) {
    return out << v.v[0] << ' ' << v.v[1] << ' ' << v.v[2] << ' ' << v.v[3];
}

inline const propix operator-(const propix& u, const propix& v) {
    return propix(u[0]-v[0], u[1]-v[1], u[2]-v[2], u.iter);
}

inline propix operator*(tReal const t, const propix &v) {
    return propix(t*v[0], t*v[1], t*v[2], v.iter);
}

inline propix operator*(const propix &v, tReal const t) {
    return t * v;
}

inline propix operator/(propix &v, tReal t) {
    return (1/t) * v;
}

// ---------- framebuffer

#include <sdl.h>

SDL_Window  *window;
SDL_Surface *buf, *surf, *gsurf;
SDL_Event   event;
SDL_Rect    rdes, rsrc;

propix      *sum, *sumwin, *gsum;
uint        *p32;
int         wm, hm, pitchBy, _idx;
int         update_modulus = 3;
bool        quit = false;

void get_pointers(SDL_Surface* srf) {
    p32 = (srf == surf) ? (uint *) surf->pixels : (uint *) buf->pixels;
    gsum = (srf == surf) ? sum : sumwin;
    pitchBy = srf->pitch / 4;
    wm = srf->w - 1;
    hm = srf->h - 1;
    rsrc.w = srf->w;
    rdes = rsrc;
    gsurf = srf;
}

void create_surface(int ww, int hh){
    if (surf != 0) return;
    surf = SDL_CreateRGBSurface(0, ww,hh, 32, 0, 0, 0, 0);
    sum = new propix[ww * hh];
    get_pointers(surf);
}

void create_window(int w, int h, bool manual_additional_surf = false){
    window = SDL_CreateWindow("SDL2 Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, 0);
    buf = SDL_GetWindowSurface(window);
    rsrc.h = 1;
    rsrc.x = 0;
    sumwin = new propix[w * h];
    get_pointers(buf);
    if (!manual_additional_surf) create_surface(w, h);
}


int found_some_color; // no .bmp if all black


int write_pixel(vec3 color, const int samps = 1) {

    gsum[_idx] += propix(color, samps);

    int value = gsum[_idx];
    p32[_idx++] = value;

    found_some_color += value != 0;  // no .bmp if all black
    return value;
}

int write_pixel_f(vec3 color, const int samps = 1) {

    gsum[_idx] += propix(color, samps);

    int value = gsum[_idx].sqr();
    p32[_idx++] = value;

    found_some_color += value != 0;  // no .bmp if all black
    return value;
}


#define framebuffer_scanline(yy)\
        _idx = (hm-yy) * pitchBy;\
        rsrc.y = hm-yy;

    //std::cout << SDL_GetError();

//            std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
//            SDL_UpdateWindowSurface(window);
//        SDL_UnlockSurface(gsurf);

#define even_more_framebu___you_get_the_point(upd_modu)\
        \
        rdes.y = rsrc.y;\
        \
        if (gsurf != buf) SDL_BlitScaled(gsurf, &rsrc, buf, &rdes);\
        if (j % upd_modu == 0) {\
            SDL_UpdateWindowSurface(window);\
            SDL_Delay(1);\
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
        \
        if (quit) break;


#define all_black (found_some_color = 0)


#define final_framebuff_stuff(delay)\
    if (!all_black && !quit && save_bmp) {\
      SDL_SaveBMP(gsurf, "output.bmp");\
    }\
    \
    SDL_Delay(delay);\
    SDL_FreeSurface(gsurf);\
    SDL_DestroyWindow(window);\
    SDL_Quit();


void propix_fill( SDL_Surface* srf,
                  vec3 col,
                  float alpha = 1 ) {
                      
    auto color = propix(col*alpha, alpha);

    get_pointers(srf);
    
    for (int j = srf->h-1; j >= 0; --j) {
        framebuffer_scanline(j)
        for (int i = 0; i < srf->w; ++i) {
            gsum[_idx] = color;
            p32[_idx++] = sum[_idx];
        }
        even_more_framebu___you_get_the_point(update_modulus)
    }
}

#endif // --- ProgressivePixel_H
