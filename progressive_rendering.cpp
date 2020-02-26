/* -- Dev-C++     -lmingw32 -lSDL2main -lSDL2

    averaging random pixels over time
    
*/

#include "common/general.h"

int main(int argc, char *argv[]) {

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface*  buf, surface;
    SDL_Event event;

    auto scale = 3.0;

    const int w = 200 * scale;
    const int h = 150 * scale;

    const int ns = 1;

    framebuffer_stuff(w,h)  // progressive_rendering.h
    
    update_modulus = 15;
    
    for (int frame = 0; frame < 10; ++frame) {
        for (int j = h-1; j >= 0; --j) {
            more_framebuffer_stuff(h)
            for (int i = 0; i < w; ++i) {
                vec3 color(0, 0, 0);
                for (int s = 0; s < ns; ++s) {
                    color += vec3(rnd, rnd, rnd);
                }
                /* sum, pixel, and idx_1d from progressive_rendering.h */
                int value = write_pixel( pixel, sum, color, idx_1d, ns );
            }
            even_more_framebu___you_get_the_point(update_modulus)
        }
        if (quit) break;
    }
    std::cerr << "\nDone.\n";
    final_framebuff_stuff(1000) // Delay

    return 0;
}

