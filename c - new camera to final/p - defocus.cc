#include "camera.h"

int main(int argc, char *argv[]) {

    auto win_scalar = 2.5;

    const int winw = 200 * win_scalar;
    const int winh = 100 * win_scalar;

    auto scale = .75;
    const int w = winw * scale;
    const int h = winh * scale;

    create_window(winw, winh,1); // manual additional surface

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

    float rad = sqrt(gw * gw + gh * gh) / 99;
    for (int frame = 299; frame >= 0; --frame) { rt_hyperparams
        for (int k = 0; k <= dots; ++k) {
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
        bool scaled = false;
        bool gamma = true;
        propix_frame(scaled, gamma);
        if (quit) break;
    }
    final_framebuff_stuff(400) // Delay

    return 0;
}

