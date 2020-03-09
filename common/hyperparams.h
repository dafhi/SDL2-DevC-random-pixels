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

void write_colp(int& imap_frame) {
    imap_frame++;
    for (int i = -1; i++ < gw*gh-1;) sum[i].colp = sum[i];
}

void importance_map(int& frame, int update_modulus=1) {
    if (frame % update_modulus == 0) {
        if (frame > 0) {
            float activ_max = 0;
            #if 0
            for (int j = gh; j-- > 0;) {
                framebuffer_scanline(j)
                for (int i = -1; i++ < wm;) {
                    #if 1
                    if (j == 257 & i == 110){
                        sum[srci+i].activ += .1;
                        float f =dcol(sum[srci+i], sum[srci+i].colp, true);
                    }
                    #endif
                    sum[srci+i].activ += dcol(sum[srci+i], sum[srci+i].colp);
                    activ_max = ffmax(activ_max, sum[srci+i].activ);
                }
            }
            #else
            for (int i = -1; i++ < gw*gh-1;) {
                sum[i].activ *= .96;
                sum[i].activ += dcol(sum[i], sum[i].colp);
                activ_max = ffmax(activ_max, sum[i].activ);
            }
            #endif
//            std::cout << "activ_max " << activ_max << " ";
            activ_max = activ_max == 0 ? 1 : 1 / activ_max;
            for (int i = -1; i++ < gw*gh-1;) sum[i].imap = sum[i].activ * activ_max;
        }
    }
    write_colp(frame);
}

#define r_uv_samps\
    ray         r;\
    float       u, v;\
    int         samps=0;

#define first_ray(i,j)\
    u = (i + rnd) / (gw);\
    v = (j + rnd) / (gh);\
    r = cam.get_ray(u, v);\
    samps++;

void low_disc_dotloop(int& imap_frame, double& dots_alpha_dilution, float rad, camera cam, _args, int max_depth, float freq = .7) {
    float box_len = rad / freq;
    if (imap_frame > 2)std::cerr << ".. Dots ";
    float dot_strength = 4 * (1 - dots_alpha_dilution);
    float slope = 1 / rad;
    for (float j = -rnd*box_len; j < gh; j+=box_len) {
        for (float i = -rnd*box_len; i < gw; i+=box_len) {
            float sj = j + rnd*box_len;
            float si = i + rnd*box_len;
            if (sj >= 0 & sj < gh & si >= 0 & si < gw) {
                int _i = si;
                int _j = sj;
                int ii = _j*pitchBy+_i;
                if (imap_frame > 0 and sum[ii].imap < .85 and rnd < .65) {

                    // low pixel activity - do nothing

                } else {
                
                    r_uv_samps
                    first_ray(_i,_j)
                    auto color = ray_color(r, _params, max_depth);
                    for (int k=1; k++ < sum[ii].imap * 4;) {
                        first_ray(_i,_j)
                        color += ray_color(r, _params, max_depth);
                    }
                    aadot::draw(si,sj,propix(color/samps,dot_strength),rad,slope);
                }
            } else {
                r_uv_samps
                first_ray(si,sj)
                auto color = ray_color(r, _params, max_depth);
                aadot::draw(si,sj,propix(color,dot_strength),rad,slope);
            }
        }
    }  dots_alpha_dilution *= .996;
}

void colp_prep(double& da_dilut, int& imap_frame, camera& cam, _args, int max_depth) {
    low_disc_dotloop(imap_frame, da_dilut, g_rad*4, cam, _params, max_depth, 1.1);
    importance_map(imap_frame);
    low_disc_dotloop(imap_frame, da_dilut, g_rad*3, cam, _params, max_depth, .8);
    importance_map(imap_frame, 1);
}

bool draw_some_dots(camera& cam, _args, int max_depth) {
    static double dots_alpha_dilution = .98;
    if (g_rad < .7071) g_rad = .7071;
    if (dots_alpha_dilution > .2) {
        static int imap_frame;
        if (imap_frame < 1) {
            colp_prep(dots_alpha_dilution, imap_frame, cam, _params, max_depth);
        }
        static float freq = .4*(2.5 - 1/imap_frame);
        low_disc_dotloop(imap_frame, dots_alpha_dilution, g_rad, cam, _params, max_depth, freq);
        importance_map(imap_frame, 1);
        g_rad *= .94;
        return true;
    }
    return false;
}

const int   strat = 15;
const float enforced_rate = (float)1 / strat;

void draw_some_pixels(camera& cam, _args, int max_depth) {
    std::cerr << ".. pixels ";
    for (int j = gh; --j >= 0;) {
        framebuffer_scanline(j)
        for (int i = 0; i < gw; ++i) {
            r_uv_samps
            if (sum[srci+i].imap >= enforced_rate) {
                first_ray(i,j)
                auto color = ray_color(r, _params, max_depth);
                for (int k=1; k++ < sum[srci+i].imap * 4;) {
                    first_ray(i,j)
                    color += ray_color(r, _params, max_depth);
                }
                write_pixel(color, i, samps);
            } else if (rnd < enforced_rate) {
                first_ray(i,j)
                auto color = ray_color(r, _params, max_depth);
                write_pixel(color, i);
            }
        }
        even_more_framebu___you_get_the_point(j, update_modulus, bool_gamma)
    }
    static int imap_frame = 1;
    importance_map(imap_frame, 2);
}

void frame_hyperparams(camera& cam, _args, int max_depth, bool scaled = false){
    initialize_profield
    update_modulus = gh;
    if ( !draw_some_dots(cam, _params, max_depth) ) {
        draw_some_pixels(cam, _params, max_depth);
    }
    bool_gamma = true;
    static int frame;
    progressive_frame(scaled, bool_gamma, frame);
}

/*
        std::cout << " " << update_modulus << " ";\
*/

#endif
