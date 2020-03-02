#include "camera.h"

int main(int argc, char *argv[]) {

    auto win_scalar = 2.5;
    auto scale = .9;

    const int winw = 200 * win_scalar;
    const int winh = 100 * win_scalar;

    const int max_depth = 50;

    create_window(winw, winh,1); // manual additional surface

    const int w = winw * scale;
    const int h = winh * scale;

//    create_surface(w,h);      // render offscreen

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

    float rad = sqrt(gw * gw + gh * gh) / 99;
    for (int frame = 299; frame >= 0; --frame) {
        rad *= .97;
        rad = ffmax(rad, .7071);
        float slope = 4/rad;
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
    final_framebuff_stuff(400) // Delay

    return 0;
}

