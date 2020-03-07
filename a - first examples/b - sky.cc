#include "../common/rtweekend.h"

vec3 ray_color(const ray& r) {
    vec3 unit_direction = unit_vector(r.direction());
    auto t = (unit_direction.y() + 1)/2;
    return (1.0-t)*vec3(1.0,1.0,1.0) + t*vec3(0.5,0.7,1.0);
}

int main(int argc, char *argv[]) {

    auto scale = 1;

    const int w = 200 * scale;
    const int h = 100 * scale;
    
    vec3 lower_left_corner(-2, -1, -1);
    vec3 horizontal(4,0,0);
    vec3 vertical(0,2,0);
    vec3 origin(0,0,0);

    create_window(w,h);

    for (int j = h-1; j >= 0; --j) {
        framebuffer_scanline(j)
        for (int i = 0; i < w; ++i) {
            auto u = float(i) / w;
            auto v = float(j) / h;
            ray r(origin, lower_left_corner + u*horizontal + v*vertical);

            vec3 color = ray_color(r);

            write_pixel( color, i );
        }
        even_more_framebu___you_get_the_point(j, update_modulus, bool_gamma)
    }
    final_framebuff_stuff(1000) // Delay

    return 0;
}

