/* -- Dev-C++     -lmingw32 -lSDL2main -lSDL2

    SDL2_and_progressive_rendering:  Aa dots demo
    
*/

#include "common/aadot.h"

void draw_some_dots(SDL_Surface* srf){
    #define border(wh,b) random_double(b, wh-1-b)

    float scale = sqrt(srf->w^2 + srf->h^2) / 32;

    int   xy_border = 20;

    for (int i=0; i<40; ++i){
        float   alpha = 2 * (1 + rnd);
        float   rad = (2 + rnd * rnd * rnd * 90) * scale;
        float   div_min = 1;
        float   div_delta = 1 - div_min;
        float   slope = div_min + (rnd * rnd * rnd) * div_delta;
        float   j = rnd;
        #define c j // j grayscale, rnd color
        aadot::draw(
            border(srf->w,xy_border),
            border(srf->h,xy_border),
            propix(c,c,c,alpha),
            rad, aadot::relative_slope(slope, rad) );
    }
}

void draw_some_stuff(SDL_Surface* srf) {
    get_pointers(srf);
    
    update_modulus = 15;
    
    SDL_LockSurface(srf);
        propix_fill(srf, vec3(.4,.7,1)*.5, 1);
        draw_some_dots(srf);
        auto p32 = (int*)srf->pixels;
        p32[50 + 50 * pitchBy] = 0xFFFFFF;
    SDL_UnlockSurface(srf);
    
    SDL_Rect r;

    r.w = srf->w;
    r.h = srf->h;
    r.x = 0;
    r.y = 0;
    SDL_BlitScaled(surf, NULL, buf, &r);

    // this works just like SDL_Flip() in SDL 1.2
    SDL_UpdateWindowSurface(window);
}

int main(int argc, char *argv[]) {

    auto win_scalar = 3;
    auto scale = .9;

    const int winw = 200 * win_scalar, w = winw * scale;
    const int winh = 150 * win_scalar, h = winh * scale;

    const int ns = 1;

    create_window( winw, winh, 1); // manual additional buffer
    create_surface( w, h);
    
    draw_some_stuff(surf);

    std::cerr << "\nDone.\n";
    final_framebuff_stuff(2000) // Delay

    return 0;
}

