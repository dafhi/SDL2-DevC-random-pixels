/*  rtweekend.h - SDL2 branch - 2020 Mar 1 - mod. from "Ray Tracing in One Weekend"

*/

#ifndef RTWEEKEND_H
#define RTWEEKEND_H

//#include <cmath>
//#include <cstdlib>
//#include <limits>
#include <memory>

// Usings

using std::shared_ptr;
using std::make_shared;

// Constants

// Common Headers
#include "aadot.h"

vec3 sky_color(const vec3& ray_d) {
    auto t = (unit_vector(ray_d).y() + 1)/2;
    return (1.0-t)*vec3(1.0,1.0,1.0) + t*vec3(0.5,0.7,1.0);
}

#define rt_uv_ij\
            float u = rnd;\
            float v = rnd;\
            float i = u * gw;\
            float j = v * gh;

#endif
