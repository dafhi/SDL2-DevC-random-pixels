/* -- hyperparams.h - 2020 Mar 3 - by dafhi

    //use:
    #include "camera.h"

    //followed by
    #include "../common/hyperparams.h"

*/

#ifndef HYPERPARAMS_H
#define HYPERPARAMS_H

#include "rtweekend.h"

#define rt_uv_ij\
            float u = rnd;\
            float v = rnd;\
            float i = u * gw;\
            float j = v * gh;

#define frame_drawdots\
            for (int k = 0; k <= dots; ++k) {\
                rt_uv_ij\
                ray r = cam.get_ray(u, v);\
                vec3 color = ray_color(r, world, max_depth);\
                aadot::draw(i,j,propix(color,1-dot_dilution),rad,slope);\
            }\
            dot_dilution *= .992;
            
/*
    In the final If block, you'll see
    auto u = .. / (gw + .5)
    
    where + .5 eliminates blurriness from aa dots crossover.
*/

#define frame_hyperparams\
        initialize_profield\
        static double dot_dilution = .98;\
        update_modulus = gh;\
        int dots = .35 * (gw * gh) / (pi * rad * rad);\
        float slope = 1 / rad;\
        bool_gamma = true;\
        vec3 color(0,0,0);\
        if (rad > .7071) {\
            frame_drawdots\
            rad *= .85;\
        } else {\
            if (dot_dilution > .39) {\
                rad = .7071;\
                frame_drawdots\
            } else {\
                static double qrate = .15;\
                qrate *= .98;\
                for (int j = hm; j >= 0; --j) {\
                    framebuffer_scanline(j)\
                    for (int i = 0; i < gw; ++i) {\
                        const float s = rnd;\
                        const bool force_sample = s < qrate;\
                        const bool imap_sample = (sum[srci+i].imap > .7);\
                        auto u = (i + rnd) / (gw + .5);\
                        auto v = (j + rnd) / (gh + .5);\
                        int samps = 0;\
                        if (force_sample) {\
                            ray const r = cam.get_ray(u, v);\
                            color = ray_color(r, world, max_depth);\
                            samps = 1;\
                        }else{\
                            color=vec3(0,0,0);\
                        }\
                        if (imap_sample) {\
                            ray r = cam.get_ray(u, v);\
                            color += ray_color(r, world, max_depth);\
                            u = (i + rnd) / (gw + .5);\
                            v = (j + rnd) / (gh + .5);\
                            r = cam.get_ray(u, v);\
                            color += ray_color(r, world, max_depth);\
                            write_pixel(color, i, 2+samps);\
                        } else if (force_sample) {\
                            write_pixel(color, i);\
                        }\
                    }\
                    even_more_framebu___you_get_the_point(j, update_modulus, bool_gamma)\
                }\
            }\
        }

#if 0
                dots_linger--;\
        std::cout << " " << dot_dilution;\
            static int dots_linger = 80;\
        std::cout << " " << update_modulus << " ";\
                sum[(int)i + (int)j*pitchBy] = color;\
            rad *= .97;
        } else {\
            static int dots_linger = 120;
        int dots = .52 * (gw * gh) / (pi * rad * rad);
#endif

#endif
