// modified from "Ray Tracing in one Weekend"

#ifndef CAMERA_H
#define CAMERA_H

#include "sphere.h"

class camera {
    public:
        camera(
            double aspect = 4/3,
            double vfov = 70, // top to bottom, in degrees
            vec3 lookfrom = vec3(0,0,0), vec3 lookat = vec3(0,0,-1),
            tReal aperture = 0, tReal focus_dist = 2, vec3 vup = vec3(0,1,0)
        ) {
            origin = lookfrom;
            lens_radius = aperture / 2;

            auto theta = degrees_to_radians(vfov);
            auto half_height = tan(theta/2) * focus_dist;
            auto half_width = aspect * half_height;
            w = unit_vector(lookfrom - lookat);
            u = unit_vector(cross(vup, w));
            v = cross(w, u);

            lower_left_corner = origin - half_width*u - half_height*v - w*focus_dist;

            horizontal = 2*half_width*u;
            vertical = 2*half_height*v;
        }

        ray get_ray(tReal s, tReal t) {
            vec3 rd = lens_radius * random_in_unit_disk();
            vec3 offset = u * rd.x() + v * rd.y();

            return ray(
                origin + offset,
                lower_left_corner + s*horizontal + t*vertical - origin - offset);
        }

    public:
        vec3 origin;
        vec3 lower_left_corner;
        vec3 horizontal;
        vec3 vertical;
        vec3 u, v, w;
        tReal lens_radius;
};

#include "../common/hyperparams.h"

#endif
