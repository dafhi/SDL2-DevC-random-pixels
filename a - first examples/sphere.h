#ifndef SPHERE_H
#define SPHERE_H

#include "material.h"

class sphere: public hittable {
    public:
        sphere() {}
        sphere(vec3 cen, tReal r) : center(cen), radius(r) {};
        virtual bool hit(
            const ray& r, tReal tmin, tReal tmax, hit_record& rec) const;

        vec3 center;
        tReal radius;
        shared_ptr<material> mat_ptr;
};

bool sphere::hit(const ray& r, tReal t_min, tReal t_max, hit_record& rec) const {
    vec3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius*radius;
    auto discriminant = half_b*half_b - a*c;

    if (discriminant > 0) {
        auto root = sqrt(discriminant);
        auto temp = (-half_b - root)/a;
        #define dupl\
        if (temp < t_max && temp > t_min) {\
            rec.t = temp;\
            rec.p = r.at(rec.t);\
            rec.normal = (rec.p - center) / radius;\
            rec.mat_ptr = mat_ptr;\
            return true;\
        }
        dupl
        temp = (-half_b + root) / a;
        dupl
    }
    return false;
}

#endif
