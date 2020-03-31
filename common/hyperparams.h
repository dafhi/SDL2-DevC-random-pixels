#ifndef HYPERPARAMS_H
#define HYPERPARAMS_H

/* -- hyperparams.h - 2020 Mar 7 - by dafhi

    ----

      usage:

    vec3 ray_color() { .. }  // from RTIOW

    #define _args           vec3 background, hittable_list world //
    #define _params         background, world

    #include "common/hyperparams.h"

        ------------------------------------------------------------

    Two drawing techs based upon propix (display pixel) class

    1.  anti-aliased dots.  size reduced over time
    2.  pixels.             rgb (uint) activity gets extra attention

        ------------------------------------------------------------

    Many other parameters.  Looking for a one-fits-all combination

*/

#include "../common/SDL2 and progressives.h"

const int g_frame__importance_trigger = 10;

void write_colp(int& frame) {
    for (int i = -1; i++ < gw*gh-1;) sum[i].colp = sum[i];
}

void rgb_delta_to_importance(int& frame, int update_modulus=1) {
    if (frame % update_modulus == 0) {

        if (frame > g_frame__importance_trigger) {
            // basic preventative measure .. If .colp is "all black", high lum gets attention

            float activ_max = 0;
            
            #if 1
                for (int i = -1; i++ < gw*gh-1;) {
                    sum[i].activ *= .93;
                    sum[i].activ += dcol(sum[i], sum[i].colp);
                    activ_max = ffmax(activ_max, sum[i].activ);
                }
            #else
                // debugger
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
            #endif
            
//            std::cout << "activ_max " << activ_max << " ";
            activ_max = activ_max == 0 ? 1 : 1 / activ_max;
            for (int i = -1; i++ < gw*gh-1;) sum[i].imap = sum[i].activ * activ_max;
        }
    }
    
    // >= here vs > near the top, meaning write_colp happens first
    if (frame >= g_frame__importance_trigger) write_colp(frame);
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
    
void plot_dot(float sj, float si, int frame, float dot_stren, float rad, camera& cam, _args, int max_dep, int _samps) {
    const float slope = 1 / rad;
    int _i = si;
    int _j = sj;
    int ii = _j*pitchBy+_i;
    
    if (sum[ii].imap < .05 and rnd < .96) {

        // low pixel activity - do nothing

    } else {

        r_uv_samps
        first_ray(_i,_j)
        auto color = ray_color(r, _params, max_dep);
        for (int k=1; k++ < sum[ii].imap * _samps;) {
            first_ray(_i,_j)
            color += ray_color(r, _params, max_dep);
        }
        aadot::draw(si,sj,propix(color/samps,dot_stren),rad,slope);
    }
}

void strat_dotloop(int& frame, double& dots_alpha_dilution, float rad, camera cam, _args, int max_depth, float freq = .7, int samps = 5) {
    if (frame > 2)std::cerr << ".. Dots ";
    const float dot_stren = 1.3 * (1 - dots_alpha_dilution);
    const float box_len = rad / freq;
    const float border = .5;
    const int   cj = gh / box_len - border;
    const int   ci = gw / box_len - border;
    const float js = (gh - cj * box_len) / 2, je = gh - .5*box_len - js;
    const float is = (gw - ci * box_len) / 2, ie = gw - .5*box_len - is;
    for (float j = js; j < je; j += box_len) {
        for (float i = is; i < ie; i += box_len) {
            plot_dot(
                j + rnd*box_len,
                i + rnd*box_len,
                frame, dot_stren, rad, cam, _params, max_depth, samps);
        }
    }  dots_alpha_dilution *= .996;
}

bool show_imap_scaled;

const int   strat = 15;
const float enforced_rate = 1.0 / strat;

void draw_some_pixels(camera& cam, _args, int max_depth, int _samps = 4) {
    std::cerr << ".. pixels ";
    for (int j = gh; --j >= 0;) {
        framebuffer_scanline(j)
        for (int i = 0; i < gw; ++i) {
            r_uv_samps
            if (sum[srci+i].imap >= enforced_rate) {
                first_ray(i,j)
                auto color = ray_color(r, _params, max_depth);
                for (int k=1; k++ < sum[srci+i].imap * _samps;) {
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
}


bool draw_some_dots(camera& cam, _args, int max_depth) {
    static double dots_alpha_dilution = .99;
    if (g_rad < .7071) g_rad = .7071;
    if (dots_alpha_dilution > .58) {
        static int imap_frame;
        const int imap_update_modulus = 1;
        static float freq = .27*(2.0 - 1/++imap_frame);
        strat_dotloop(imap_frame, dots_alpha_dilution, g_rad, cam, _params, max_depth, freq);
        rgb_delta_to_importance(imap_frame, imap_update_modulus);
        g_rad *= .96;
        return true;
    }
    return false;
}

void frame_hyperparams(camera& cam, _args, int max_depth, bool scaled = false){
    initialize_profield
    update_modulus = gh;
    bool_gamma = true;
    show_imap_scaled = scaled; // instructional
    if ( !draw_some_dots(cam, _params, max_depth) ) {
        draw_some_pixels(cam, _params, max_depth);
        static int imap_frame = 1;
        rgb_delta_to_importance(imap_frame, 2);
    }
    static int frame;
    show_render(scaled, bool_gamma, frame++);
}

#endif
