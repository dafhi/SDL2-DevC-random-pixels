/*

    Improved metal replaces lambertian; just set fuzz close to 1.
    
    I've placed ray_color() at the end of material.h
    
*/

#include "camera.h"

int main(int argc, char *argv[]) {

    auto win_scalar = 3;

    const int winw = 200 * win_scalar;
    const int winh = 100 * win_scalar;

    const int max_depth = 50;

    auto scale = .95;
    const int w = winw * scale;
    const int h = winh * scale;

    create_window(winw, winh); // manual additional surface

    create_surface(w,h);

    hittable_list world;

    #if 1
    
    world.add(make_shared<sphere>(
        vec3(0,0,-1), 0.5, make_shared<lambertian>(vec3(0.7, 0.3, 0.3), .4)));

    world.add(make_shared<sphere>(
        vec3(0,-100.5,-1), 100, make_shared<metal>(vec3(0.8, 0.8, 0.0), 1)));

    world.add(make_shared<sphere>(vec3(1,0,-1), 0.5, make_shared<metal>(vec3(0.8, 0.6, 0.2), .0)));
    world.add(make_shared<sphere>(vec3(-1,0,-1), 0.5, make_shared<metal>(vec3(0.8, 0.8, 0.8), .0)));
    #else
    
    world.add(make_shared<sphere>(
        vec3(0,0,-1), 0.5, make_shared<lambertian>(vec3(0.1, 0.2, 0.5))));
        
    world.add(make_shared<sphere>(
        vec3(0,-100.5,-1), 100, make_shared<lambertian>(vec3(0.8, 0.8, 0.0), .8)));
        
    world.add(make_shared<sphere>(vec3(1,0,-1), 0.5, make_shared<metal>(vec3(0.8, 0.6, 0.2), 0.3)));
    world.add(make_shared<sphere>(vec3(-1,0,-1), 0.5, make_shared<dielectric>(1.5)));
    world.add(make_shared<sphere>(vec3(-1,0,-1), -0.45, make_shared<dielectric>(1.5)));
    #endif
    
    auto lookfrom = vec3(3,2,2)*1;
    vec3 lookat(0,0,-1);
    
    auto dist_to_focus = (lookfrom-lookat).length();
    auto aperture = 1.0;
    
    camera cam(w/h, 20, lookfrom, lookat, aperture, dist_to_focus);

    for (int frame = 50; frame >= 0; --frame) {
        std::cerr << "\rframes remaining:  " << frame << " " << std::flush;
        bool scaled = false;
        frame_hyperparams(cam, world, max_depth, scaled);
        if (quit) break;
    }
    final_framebuff_stuff(1000)

    return 0;
}

