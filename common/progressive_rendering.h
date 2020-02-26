/*
    progressive pixel class and SDL2 encapsulation defines
    2020 Feb 15 - by dafhi
*/

#ifndef ProgressivePixel_H
#define ProgressivePixel_H

#include "vec3.h"

class ProgressivePixel {
      public:

    operator auto() const { a / iter; }
    const float operator[](int i) const { return a.e[i]/iter; }

    ProgressivePixel& operator+=(const vec3 &v) {
        a += v;
        iter ++;
        return *this;
    }

    ProgressivePixel& operator*=(const tReal t) {
        a *= t;
        iter *= t;
        return *this;
    }

    ProgressivePixel& operator/=(const tReal t) {
        return *this *= 1/t;
    }

    vec3  a;
    float iter; // float allows filtering options
};

#include <sdl.h>


// framebuffer

inline uint rgb(int r, int g, int b){
   return r << 16 | g << 8 | b;
}

inline uint rgb_f(float r, float g, float b) {

  #define clamp255(f)   f <= 0 ? 0 : f < 1 ? 256 * (f) : 255
  #define i255(f)       clamp255(f)

  return rgb( i255(r), i255(g), i255(b) );
}

int found_some_color; // no .bmp if all black

int write_pixel(int* pixel,
                ProgressivePixel* sum,
                vec3 color,
                int& idx_1d,
                const int samps = 1 ) {

    #define col sum[idx_1d]

    col += color / samps;
    int value = rgb_f( col[0], col[1], col[2] );
    pixel[idx_1d++] = value;
    found_some_color += value != 0;  // cancel .bmp if all black
    return value;
}

#define framebuffer_stuff(w,h)\
    window = SDL_CreateWindow( "SDL2",\
      SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,\
      w, h, SDL_WINDOW_RESIZABLE );\
    \
    renderer = SDL_CreateRenderer(window, -1, 0);\
    SDL_SetRenderTarget(renderer, NULL);\
    buf = SDL_GetWindowSurface(window);\
    \
    int pix_value;\
    bool quit = false;\
    auto *sum = new ProgressivePixel[w * h];\
    int pitchBy = buf->pitch / 4;\
    int update_modulus = 3;

#define more_framebuffer_stuff(bufh)\
        int *pixel = (int *)buf->pixels;\
        int idx_1d = (bufh-1-j) * pitchBy;\
        \
        SDL_LockSurface(buf);

#define even_more_framebu___you_get_the_point(upd_modu)\
        SDL_UnlockSurface(buf);\
        SDL_UpdateWindowSurface(window);\
        \
        if (j % upd_modu == 0) {\
            std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;\
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

#define final_framebuff_stuff(delay)\
    if (!all_black && !quit && save_bmp) {\
      SDL_SaveBMP(buf, "output.bmp");\
    }\
    \
    SDL_Delay(delay);\
    SDL_DestroyRenderer(renderer);\
    SDL_Quit();

bool save_bmp = false; // save after render completion

#define all_black (found_some_color = 0)

#endif // --- ProgressivePixel_H
