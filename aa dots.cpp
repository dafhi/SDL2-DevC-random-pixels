/* -- Dev-C++     -lmingw32 -lSDL2main -lSDL2

    Anti-aliased dots.

*/

#include "common/aadot.h"

void draw_some_dots(SDL_Surface* srf){
    #define border(wh,bor) random_double(bor, wh-1-bor)

    float scale = sqrt(srf->w^2 + srf->h^2) / 32;

    int   xy_border = 5;

    for (int i=0; i<40; ++i){
        float   alpha = 1 * (.5 + rnd);
        float   rad = (4 + rnd * rnd * rnd * 200) * scale;
        float   slope = 1 * (1 + 2 * rnd * rnd);
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
    
    initialize_profield  /* not needed if your renderer calls either:
       frame_hyperparams()
       framebuffer_scanline() */

    SDL_LockSurface(srf);
        propix_fill(srf, vec3(.4,.7,1)*.1, .1);
        draw_some_dots(srf);
    SDL_UnlockSurface(srf);

    bool scaled = false;
    bool gamma = false;
    progressive_frame(scaled, gamma);
}

int main(int argc, char *argv[]) {

    auto scale = 3.0;
    const int winw = 200 * scale;
    const int winh = 150 * scale;

    scale = .7;
    const int w = winw * scale;
    const int h = winh * scale;

    create_window(winw, winh);
    create_surface(w, h);
    
    draw_some_stuff(gsurf);

    final_framebuff_stuff(2000) // Delay

    return 0;
}

