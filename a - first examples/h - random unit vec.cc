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

    auto win_scalar = 4;

    const int winw = 200 * win_scalar;
    const int winh = 100 * win_scalar;

    create_window(winw, winh,1); // manual additional surface

    auto scale = .9;

    const int w = winw * scale;
    const int h = winh * scale;

    create_surface(w,h);      // render offscreen

    hittable_list world;
    world.add(make_shared<sphere>(vec3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(vec3(0,-100.5,-1), 100));
    camera cam;

    const int max_depth = 50;
    
    propix_fill( gsurf, vec3(0,0,0), .001);

    float rad = sqrt(gw * gw + gh * gh) / 99;
    for (int frame = 199; frame >= 0; --frame) { rt_hyperparams
        for (int k = 0; k < dots; ++k) {
            #if 0
            int i = rnd * gw;
            int j = rnd * gh;
            auto u = (i + rnd) / gw;
            auto v = (j + rnd) / gh;
            #else
            float i = rnd * (gw);
            float j = rnd * (gh);
            auto u = (i) / gw;
            auto v = (j) / gh;
            #endif
            ray r = cam.get_ray(u, v);
            vec3 color = ray_color(r, world, max_depth);
            aadot::draw(i,hm-j,propix(color,1),rad,slope);
        }
        auto scaled = false;
        auto gamma = true;
        propix_frame(scaled, gamma);
        if (quit) break;
    }
    std::cerr << "\nDone.\n";
    final_framebuff_stuff(800) // Delay

    return 0;
}

