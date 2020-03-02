#include "camera.h"

hittable_list random_scene() {
    hittable_list objects;

    objects.add(make_shared<sphere>(
        vec3(0,-1000,0), 1000, make_shared<lambertian>(vec3(0.5, 0.5, 0.5))));

    int i = 1;
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            vec3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());
            if ((center - vec3(4, 0.2, 0)).length() > 0.9) {
                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = vec3::random() * vec3::random();
                    objects.add(
                        make_shared<sphere>(center, 0.2, make_shared<lambertian>(albedo)));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = vec3::random(.5, 1);
                    auto fuzz = random_double(0, .5);
                    objects.add(
                        make_shared<sphere>(center, 0.2, make_shared<metal>(albedo, fuzz)));
                } else {
                    // glass
                    objects.add(make_shared<sphere>(center, 0.2, make_shared<dielectric>(1.5)));
                }
            }
        }
    }

    objects.add(make_shared<sphere>(vec3(0, 1, 0), 1.0, make_shared<dielectric>(1.5)));

    objects.add(
        make_shared<sphere>(vec3(-4, 1, 0), 1.0, make_shared<lambertian>(vec3(0.4, 0.2, 0.1))));

    objects.add(
        make_shared<sphere>(vec3(4, 1, 0), 1.0, make_shared<metal>(vec3(0.7, 0.6, 0.5), 0.0)));

    return objects;
}

int main(int argc, char *argv[]) {

    auto win_scalar = 1.5;
    auto scale = .9;

    const int winw = 200 * win_scalar;
    const int winh = 100 * win_scalar;
    
    const int max_depth = 50;

    create_window(winw, winh,1); // manual additional surface

    const int w = winw * scale;
    const int h = winh * scale;

//    create_surface(w,h);      // render offscreen

    auto world = random_scene();

    const auto aspect_ratio = tReal(w) / h;
    vec3 lookfrom(13,2,3);
    vec3 lookat(0,0,0);
    tReal dist_to_focus = 10.0;
    tReal aperture = 0.1;
    tReal vfov = 20;
    camera cam(aspect_ratio, vfov, lookfrom, lookat, aperture, dist_to_focus, vec3(0,1,0));

    float rad = sqrt(gw * gw + gh * gh) / 99;
    for (int frame = 199; frame >= 0; --frame) {
        rad *= .975; // talkin' about them hyper-parameters
        rad = ffmax(rad, .7071);
        float slope = 1 / rad;
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

