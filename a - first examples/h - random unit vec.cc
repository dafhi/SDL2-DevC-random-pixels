#include "camera.h"

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

    auto win_scalar = 3;
    auto scale = .9;

    const int winw = 200 * win_scalar;
    const int winh = 100 * win_scalar;

    const int max_depth = 50;

    create_window(winw, winh,1); // manual additional surface

    const int w = winw * scale;
    const int h = winh * scale;

//    create_surface(w,h);      // render offscreen

    hittable_list world;
    world.add(make_shared<sphere>(vec3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(vec3(0,-100.5,-1), 100));
    camera cam;

    float rad = sqrt(gw * gw + gh * gh) / 99;
    for (int frame = 299; frame >= 0; --frame) {
        rad *= .97;
        rad = ffmax(rad, .7071);
        float slope = 4 / rad;
        int dots = .45 * (gw * gh) / (pi * rad * rad) + 1;
        std::cerr << "\rframes remaining:  " << frame << " " << std::flush;;
        for (int k = 0; k < dots; ++k) {
            int i = rnd * gw;
            int j = rnd * gh;
            auto u = (i + rnd) / gw;
            auto v = (j + rnd) / gh;
            ray r = cam.get_ray(u, v);
            vec3 color = ray_color(r, world, max_depth);
            aadot::draw(i,hm-j,propix(color,1),rad,slope);
        }
        propix_frame();
        if (quit) break;
    }
    std::cerr << "\nDone.\n";
    final_framebuff_stuff(800) // Delay

    return 0;
}

