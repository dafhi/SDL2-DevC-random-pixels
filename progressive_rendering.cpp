/* -- Dev-C++     -lmingw32 -lSDL2main -lSDL2

    averaging pixels over time
    
*/

#include "common/aadot.h"

int main(int argc, char *argv[]) {

    auto win_scalar = 3;
    
    const int winw = 200 * win_scalar;
    const int winh = 150 * win_scalar;

    const int ns = 1;

    auto scale = .9;

    const int w = winw * scale;
    const int h = winh * scale;

    create_window(winw,winh);
    create_surface(w,h);

    update_modulus = 3;
    
    for (int frame = 0; frame < 10; ++frame) {
        bool gamma = false;
        for (int j = 0; j < gh; ++j) {
            framebuffer_scanline(j)
            for (int i = 0; i < gw; ++i) {
                vec3 color(0, 0, 0);
                for (int s = 0; s < ns; ++s) {
                    color += vec3(rnd, rnd, rnd);
                }
                write_pixel(color, i, ns);
            }
            even_more_framebu___you_get_the_point(j, update_modulus, gamma)
        }
        if (quit) break;
    }
    final_framebuff_stuff(1000) // Delay

    return 0;
}

