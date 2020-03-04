#include "../common/rtweekend.h"

int main(int argc, char *argv[]) {

    auto scale = 1;

    const int w = 200 * scale;
    const int h = 100 * scale;
    
    create_window(w,h);
    for (int j = hm; j >= 0; --j) {
        framebuffer_scanline(j)
        for (int i = 0; i < w; ++i) {
            auto r = float(i) / w;
            auto g = float(j) / h;
            auto b = .2;

            vec3 color = vec3(r,g,b);

            write_pixel( color, i );
        }
        even_more_framebu___you_get_the_point(j, update_modulus, bool_gamma)
    }
    final_framebuff_stuff(1000)

    return 0;
}

