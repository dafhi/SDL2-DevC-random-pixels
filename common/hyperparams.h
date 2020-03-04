/* -- hyperparams.h - 2020 Mar 3 - by dafhi

    //use:
    #include "camera.h"

    //followed by
    #include "../common/hyperparams.h"

*/

#ifndef HYPERPARAMS_H
#define HYPERPARAMS_H

#include "rtweekend.h"

#define frame_drawdots\
            for (int k = 0; k <= dots; ++k) {\
                rt_uv_ij\
                ray r = cam.get_ray(u, v);\
                vec3 color = ray_color(r, world, max_depth);\
                aadot::draw(i,j,propix(color,.15),rad,slope);\
            }\
            
/*
    In the final If block, you'll see
    auto u = .. / (gw + .5)
    
    where + .5 eliminates blurriness from aa dots crossover.
*/

#define frame_hyperparams\
        initialize_profield\
        int dots = .52 * (gw * gh) / (pi * rad * rad);\
        float slope = 6 / rad;\
        bool_gamma = true;\
        if (rad > .7071) {\
            frame_drawdots\
            rad *= .97;\
        } else {\
            static int dots_linger = 250;\
            if (dots_linger) {\
                frame_drawdots\
                dots_linger--;\
            } else {\
                float u_mult = 1 / (gw + .5);\
                float v_mult = 1 / (gh + .5);\
                for (int j = hm; j >= 0; --j) {\
                    framebuffer_scanline(j)\
                    for (int i = 0; i < gw; ++i) {\
                        auto u = (i + rnd) * u_mult;\
                        auto v = (j + rnd) * v_mult;\
                        ray r = cam.get_ray(u, v);\
                        vec3 color = ray_color(r, world, max_depth);\
                        write_pixel(color, i);\
                    }\
                    even_more_framebu___you_get_the_point(j, update_modulus, bool_gamma)\
                }\
            }\
        }

#endif
