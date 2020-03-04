#include "camera.h"
#include "../common/hyperparams.h"

vec3 ray_color(const ray& r, const hittable& world, int depth) {
    hit_record rec;
    if (world.hit(r, 0.001, infinity, rec)) {
        // If we've exceeded the ray bounce limit, no more light is gathered.
        if (depth <= 0)
            return vec3(0,0,0);
        vec3 target = rec.p + rec.normal + random_unit_vector();
        return 0.5 * ray_color(ray(rec.p, target - rec.p), world, depth-1);
    }
    return sky_color(r.d());
}

int main(int argc, char *argv[]) {

    auto scale = 5.0;

    const int winw = 200 * scale;
    const int winh = 100 * scale;

    create_window(winw, winh);

    scale = 1;

    const int w = winw * scale;
    const int h = winh * scale;

    create_surface(w,h);      // render offscreen

    hittable_list world;
    world.add(make_shared<sphere>(vec3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(vec3(0,-100.5,-1), 100));
    camera cam;

    const int max_depth = 50;
    
    for (int frame = 299; frame >= 0; --frame) {
        frame_hyperparams
        std::cerr << "\rframes remaining:  " << frame << " " << std::flush;
        auto scaled = false;
        propix_frame(scaled, bool_gamma);
        if (quit) break;
//        SDL_Delay(10);
    }
    final_framebuff_stuff(800) // Delay

    return 0;
}

