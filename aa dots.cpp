/* -- Dev-C++     -lmingw32 -lSDL2main -lSDL2

    Anti-aliased dots.
    I like these guys.

*/

//  Gamma may be set for ray-tracing.
//  You can change it in SDL2_and_progressive_rendering.h
#include "common/aadot.h"

void draw_some_dots(SDL_Surface* srf){
    #define border(wh,b) random_double(b, wh-1-b)

    float scale = sqrt(srf->w^2 + srf->h^2) / 32;

    int   xy_border = 20;

    for (int i=0; i<40; ++i){
        float   alpha = 2 * (.5 + rnd);
        float   rad = (4 + rnd * rnd * 90) * scale;
        float   slope = 1.5 * (.5 + rnd);
        float   j = rnd;
        #define c rnd // j grayscale, rnd color
        aadot::draw(
            border(srf->w,xy_border),
            border(srf->h,xy_border),
            propix(c,c,c,alpha),
            rad, aadot::relative_slope(slope, rad) );
    }
}

void draw_some_stuff(SDL_Surface* srf) {
    if (srf==0) return;
    get_pointers(srf);
    update_modulus = gh;

//    SDL_LockSurface(srf);
        propix_fill(srf, vec3(.4,.7,1)*.5, .1);
        draw_some_dots(srf);
        p32 = (uint*)srf->pixels;
        p32[50 + 50 * pitchBy] = 0xFFFFFF;
//    SDL_UnlockSurface(srf);

    propix_frame();

    SDL_Rect r;
    r.w = srf->w;
    r.h = srf->h;
    r.x = 0;
    r.y = 0;
    SDL_BlitScaled(surf, NULL, buf, &r);
}

int main(int argc, char *argv[]) {

    auto win_scalar = 3;

    const int winw = 200 * win_scalar;
    const int winh = 150 * win_scalar;

    auto scale = .9;

    const int w = winw * scale;
    const int h = winh * scale;

    create_window( winw, winh, 1); // manual additional buffer
    create_surface( w, h);
    
    draw_some_stuff(gsurf);

    // this works just like SDL_Flip() in SDL 1.2
    SDL_UpdateWindowSurface(window);

    std::cerr << "\nDone.\n";
    final_framebuff_stuff(2000) // Delay

    return 0;
}

