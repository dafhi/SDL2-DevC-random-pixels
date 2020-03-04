#ifndef COMMON_H
#define COMMON_H

#include "camera.h"

void draw_dots(camera &cam, hittable_list world, int max_depth = 50) {

}

void draw_pixels(int w, int h, vec3 ori, vec3 llc, vec3 hori, vec3 vert) {
}

#define frame_hyperparams\
        initialize_profield\
        bool bool_pixels = false;\
        rad = ffmax(.7,rad);\
        if (rad > .65) {\
            \
            float slope = 6 / rad;\
            int dots = .53 * (gw * gh) / (pi * rad * rad);\
            for (int k = 0; k <= dots; ++k) {\
                rt_uv_ij\
                ray r = cam.get_ray(u, v);\
                vec3 color = ray_color(r, world, max_depth);\
                aadot::draw(i,gh-j,propix(color,.15),rad,slope);\
            }\
            rad *= .965;\
        } else {\
            bool gamma = true;\
            for (int j = hm; j >= 0; --j) {\
                framebuffer_scanline(j)\
                for (int i = 0; i < gw; ++i) {\
                    auto u = (i + rnd) / gw;\
                    auto v = (j + rnd) / gh;\
                    ray r = cam.get_ray(u, v);\
                    vec3 color = ray_color(r, world, max_depth);\
                    write_pixel(color, _idx++);\
                }\
                even_more_framebu___you_get_the_point(j, update_modulus, gamma)\
            }\
        }

#endif
