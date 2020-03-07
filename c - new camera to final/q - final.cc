#include "camera.h"

hittable_list random_scene() {
    hittable_list objects;

    objects.add(make_shared<sphere>(
        vec3(0,-1000,0), 1000, make_shared<metal>(vec3(0.5, 0.5, 0.5), 1)));

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

    float scale = 2.5;

    const int winw = 200 * scale;
    const int winh = 100 * scale;
    
    const int max_depth = 50;

    scale = .97;
    const int w = winw * scale;
    const int h = winh * scale;

    create_window(winw, winh);
    create_surface(w,h);

    auto world = random_scene();

    const auto aspect_ratio = tReal(w) / h;
    vec3 lookfrom(13,2,3);
    vec3 lookat(0,0,0);
    tReal dist_to_focus = 10.0;
    tReal aperture = 0.1;
    tReal vfov = 20;
    camera cam(aspect_ratio, vfov, lookfrom, lookat, aperture, dist_to_focus);
    
    for (int frame = 30; frame >= 0; --frame) {
        bool scaled = false;
        frame_hyperparams(frame, cam, world, max_depth, scaled);
        std::cerr << "\rframes remaining:  " << frame << " " << std::flush;
        if (quit) break;
    }
    
//    save_bmp = true;
    final_framebuff_stuff(1000)

    return 0;
}

