/* -- hyperparams.h - 2020 Mar 5 - by dafhi

    uses code from "Ray Tracing in one Weekend"

    #include "camera.h"
    #include "../common/hyperparams.h"

        ----------------

    2 drawing techs

    1.  anti-aliased dots.  size reduced over time
    2.  pixels.             high uint activity gets extra attention

*/

#ifndef HYPERPARAMS_H
#define HYPERPARAMS_H

#include "rtweekend.h" // "Ray Tracing in one Weekend"

void importance_map(int frame) {
    if (frame % 3 == 0) return;
    activ_max = 0;
    for (int j = gh; --j > 0;) {
        framebuffer_scanline(j)
        for (int i = 0; i++ < wm;) {
            int temp = sum[srci+i].gamma();
            sum[srci+i].calc_activ(temp);
            sum[srci+i].colp = temp;
            activ_max = ffmax(activ_max, sum[srci+i].activ);
            p32[desi+i] = temp;
        }
    }
    activ_max = (activ_max == 0) ? 1 : 1 / activ_max;
    for (int i = 0; i++ < gw*gh-1;) sum[i].imap = sum[i].activ * activ_max;
}

#define frame_drawdots\
    std::cerr << ".. Dots ";\
    for (int k = 0; k <= dots; ++k) {\
        float u = rnd;\
        float v = rnd;\
        float i = u * gw;\
        float j = v * gh;\
        ray r = cam.get_ray(u, v);\
        vec3 color = ray_color(r, world, max_depth);\
        aadot::draw(i,j,propix(color,dot_strength),rad,slope);\
    }\
    importance_map(frame);\
    propix_frame(scaled, bool_gamma);\
    dot_dilution *= .98;

bool draw_some_dots(int frame, camera cam, hittable_list world, int max_depth, bool scaled=false) {
    static double dot_dilution = .98;
    int dots = .4 * (gw * gh) / (pi * rad * rad);
    float slope = 1.7 / rad;
    float dot_strength = 1.1*(1 - dot_dilution);
    if (rad > 1.5) { frame_drawdots; rad *= .7; return true; }
    if (dot_dilution > .47) { frame_drawdots; return true; }
    return false;
}

// + .5 eliminates blurriness from aa dots crossover, which suggests:

// "off by one"-ish bug type in the camera class
// problem with my aa dots

#define initial_ray\
    u = (i + rnd) / (gw + .5);\
    v = (j + rnd) / (gh + .5);\
    r = cam.get_ray(u, v);\
    samps++;

void draw_some_pixels(int frame, camera cam, hittable_list world, int max_depth, bool scaled = false) {
    static double enforced_rate = .29;
    std::cerr << ".. pixels ";
    for (int j = gh; --j >= 0;) {
        framebuffer_scanline(j)
        for (int i = 0; i < gw; ++i) {
            const float s = rnd;
            const bool  brute_sample = (s < enforced_rate);
            ray         r;
            float       u, v;
            int         samps = 0;
            vec3        color;
            if (brute_sample) {
                initial_ray;
                color = ray_color(r, world, max_depth);
            }
            const bool  imap_sample = sum[srci+i].imap > .7; // some threshold
            if (imap_sample) {
                for (int k=1; k++ <= sum[srci+i].imap * 10;) {
                    initial_ray
                    color += ray_color(r, world, max_depth);
                }
                write_pixel(color, i, samps);
            }else if (brute_sample) {
                write_pixel(color, i);
            }
        }
        even_more_framebu___you_get_the_point(j, update_modulus, bool_gamma)
    }
    importance_map(frame);
    enforced_rate *= .997;
}

void frame_hyperparams(int frame, camera cam, hittable_list world, int max_depth, bool scaled = false){
    initialize_profield
    update_modulus = gh;
    bool_gamma = true;
    if ( !draw_some_dots(frame, cam, world, max_depth, scaled) ) {
        draw_some_pixels(frame, cam, world, max_depth, scaled);
    }
}

#if 0
        std::cout << " " << dot_dilution;\
        std::cout << " " << update_modulus << " ";\
                sum[(int)i + (int)j*pitchBy] = color;\
        } else {\
        int dots = .52 * (gw * gh) / (pi * rad * rad);
#endif

#endif
