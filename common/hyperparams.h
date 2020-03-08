#ifndef HYPERPARAMS_H
#define HYPERPARAMS_H

/* -- hyperparams.h - 2020 Mar 7 - by dafhi

        techs

    1.  anti-aliased dots.  size reduced over time
    2.  pixels.             rgb (uint) activity gets extra attention


    -- usage
    
    vec3 ray_color() { .. }

    #define _args           vec3 background, hittable_list world //
    #define _params         background, world

    #include "common/hyperparams.h"
*/


#include "../common/aadot.h"

#define radiance_string ray_color(r, _params, max_depth)

void importance_map(int frame, int update_modulus) {
    float activ_max = 0;
    if (frame % update_modulus == 0) {
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
}

#define r_uv_samps\
    ray         r;\
    float       u, v;\
    int         samps=0;

#define first_ray\
    u = (i + rnd) / (gw);\
    v = (j + rnd) / (gh);\
    r = cam.get_ray(u, v);\
    samps++;

#define frame_drawdots\
    std::cerr << ".. Dots ";\
    importance_map(frame, 1);\
    for (int k = 0; k <= dots; ++k) {\
        float si = rnd * gw;\
        float sj = rnd * gh;\
        int i = si;\
        int j = sj;\
        int ii = j*pitchBy+i;\
        if (sum[ii].imap < .1 & rnd < .9) continue;\
        r_uv_samps\
        first_ray\
        auto color = radiance_string;\
        for (int k=1; k++ < sum[ii].imap * 4;) {\
            first_ray\
            color += radiance_string;\
        }\
        aadot::draw(si,sj,propix(color/samps,dot_strength),rad,slope);\
    }\
    aadots_alpha_dilution *= .996;

bool draw_some_dots(int frame, camera cam, _args, int max_depth) {
    static double aadots_alpha_dilution = .98;
    int dots = 1.2 * (gw * gh) / (pi * rad * rad);
    float slope = 1 / rad;
    float dot_strength = 1.9*(1 - aadots_alpha_dilution);
    if (rad > .7071) { frame_drawdots; rad *= .87; return true; } rad = .7071;
    if (aadots_alpha_dilution > .47) { frame_drawdots; return true; }
    return false;
}

const int   strat = 15;
const float enforced_rate = (float)1 / strat;

void draw_some_pixels(int frame, camera cam, _args, int max_depth) {
    std::cerr << ".. pixels ";
    for (int j = gh; --j >= 0;) {
        framebuffer_scanline(j)
        for (int i = 0; i < gw; ++i) {
            r_uv_samps
            if (sum[srci+i].imap >= enforced_rate) {
                first_ray
                auto color = radiance_string;
                for (int k=1; k++ < sum[srci+i].imap * 4;) {
                    first_ray
                    color += radiance_string;
                }
                write_pixel(color, i, samps);
            } else if (rnd < enforced_rate) {
                first_ray
                auto color = radiance_string;
                write_pixel(color, i);
            }
        }
        even_more_framebu___you_get_the_point(j, update_modulus, bool_gamma)
    }
    importance_map(frame, 1);
}

void frame_hyperparams(int frame, camera cam, _args, int max_depth, bool scaled = false){
    initialize_profield
    update_modulus = gh;
    if ( !draw_some_dots(frame, cam, _params, max_depth) ) {
        draw_some_pixels(frame, cam, _params, max_depth);
    }
    bool_gamma = true;
    progressive_frame(scaled, bool_gamma, frame);
}

/*
        std::cout << " " << update_modulus << " ";\
// + .5 eliminates blurriness from aa dots crossover which suggests problem with
*/

#endif
