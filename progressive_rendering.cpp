/* -- Dev-C++     -lmingw32 -lSDL2main -lSDL2

    averaging pixels over time
    
*/

#include "common/aadot.h"

int main(int argc, char *argv[]) {

    auto win_scalar = 3;

    const int winw = 200 * win_scalar;
    const int winh = 150 * win_scalar;

    auto scale = .9;
    
    const int w = winw * scale;
    const int h = winh * scale;

    create_window(winw,winh,1);
    create_surface(w,h);
    
    const int ns = 1;

    update_modulus = 10;
    
    for (int frame = 0; frame < 15; ++frame) {
        for (int j = hm; j >= 0; --j) {
            framebuffer_scanline(j)
            for (int i = 0; i < w; ++i) {
                vec3 color(0, 0, 0);
                for (int s = 0; s < ns; ++s) {
                    color += vec3(rnd, rnd, rnd);
                }
                int value = write_pixel(color, ns); // sqrt, linear: write_pixel_f, write_pixel
            }
            even_more_framebu___you_get_the_point(update_modulus)
        }
        if (quit) break;
    }
    std::cerr << "\nDone.\n";
    final_framebuff_stuff(1000) // Delay

    return 0;
}

