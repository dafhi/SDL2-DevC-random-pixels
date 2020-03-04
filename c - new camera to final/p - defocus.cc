#include "camera.h"
#include "../common/hyperparams.h"

int main(int argc, char *argv[]) {

    auto win_scalar = 5;

    const int winw = 200 * win_scalar;
    const int winh = 100 * win_scalar;

    auto scale = .9;
    const int w = winw * scale;
    const int h = winh * scale;

    create_window(winw, winh); // manual additional surface

    create_surface(w,h);

    const int max_depth = 50;

    hittable_list world;

    #if 1
    world.add(make_shared<sphere>(
        vec3(0,0,-1), 0.5, make_shared<lambertian>(vec3(0.7, 0.3, 0.3))));

    world.add(make_shared<sphere>(
        vec3(0,-100.5,-1), 100, make_shared<lambertian>(vec3(0.8, 0.8, 0.0))));

    world.add(make_shared<sphere>(vec3(1,0,-1), 0.5, make_shared<metal>(vec3(0.8, 0.6, 0.2))));
    world.add(make_shared<sphere>(vec3(-1,0,-1), 0.5, make_shared<metal>(vec3(0.8, 0.8, 0.8))));

    #else
    world.add(make_shared<sphere>(vec3(0,0,-1), 0.5, make_shared<lambertian>(vec3(0.1, 0.2, 0.5))));
    world.add(make_shared<sphere>(
        vec3(0,-100.5,-1), 100, make_shared<lambertian>(vec3(0.8, 0.8, 0.0))));
    world.add(make_shared<sphere>(vec3(1,0,-1), 0.5, make_shared<metal>(vec3(0.8, 0.6, 0.2), 0.3)));
    world.add(make_shared<sphere>(vec3(-1,0,-1), 0.5, make_shared<dielectric>(1.5)));
    world.add(make_shared<sphere>(vec3(-1,0,-1), -0.45, make_shared<dielectric>(1.5)));
    #endif
    
    vec3 lookfrom(3,3,2);
    vec3 lookat(0,0,-1);
    vec3 vup(0,1,0);
    auto dist_to_focus = (lookfrom-lookat).length();
    auto aperture = 2.0;
    
    camera cam(w/h, 20, lookfrom, lookat, aperture, dist_to_focus, vup);
    //camera cam(90, aspect_ratio);

    for (int frame = 199; frame >= 0; --frame) {
        frame_hyperparams
        std::cerr << "\rframes remaining:  " << frame << " " << std::flush;
        auto scaled = false;
        propix_frame(scaled, bool_gamma);
        if (quit) break;
    }
    final_framebuff_stuff(400) // Delay

    return 0;
}

