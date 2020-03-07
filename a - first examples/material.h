/*
    modded material header from "Ray Tracing in one Weekend"
    */

#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable_list.h"

class material {
    public:
        virtual bool scatter(
            const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered
        ) const = 0;
    vec3 albedo;
};

class lambertian : public material {
        public:

    // param 2 makes hand-typed material switching easier
    lambertian(const vec3& a=vec3(1,1,1), float dummy_var=0) { albedo = a; }

    virtual bool scatter(
        const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered
    ) const {
        vec3 scatter_direction = rec.normal + random_unit_vector();
        scattered = ray(rec.p, scatter_direction);
        attenuation = albedo;
        return true;
    }

};

class metal : public material {
        public:
    metal(const vec3& a, float f=0) {albedo = a; fuzz = f;}

    virtual bool scatter(
        const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered
    ) const {
    
        #if 0
        
            // "Ray Tracing in one Weekend"
            vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
            scattered = ray(rec.p, reflected + fuzz*random_in_unit_sphere());
        #else
        
            // original "metal" scattering concept goes from perfect mirror
            // to a very close lambertian approximation. (probs a bug in my code)
            vec3 reflected = reflect(r_in.direction(), fuzzy_norm(r_in.direction(), rec.normal, fuzz));
            scattered = ray(rec.p, reflected);
        #endif

        scattered = ray(rec.p, reflected);
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }

    float fuzz;
};

#endif
