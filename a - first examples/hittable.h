/* -- hittable_list -

    from "Ray Tracing in one Weekend"

*/

#ifndef HITTABLE_H
#define HITTABLE_H

#include "../common/rtweekend.h"

class material;

struct hit_record {
    vec3 p;
    vec3 normal;
    shared_ptr<material> mat_ptr;
    tReal t;
};

class hittable {
    public:
        virtual bool hit(const ray& r, tReal t_min, tReal t_max, hit_record& rec) const = 0;
};

#endif
