// modified from "Ray Tracing in one Weekend"

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

    metal(const vec3& a=vec3(1,1,1), tReal f = 0.1)  { albedo = a; fuzz = f; }

    virtual bool scatter(
        const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered
    ) const {
    
        attenuation = albedo;
        #if 0
        
            // Ray Tracing in one Weekend
            vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
            scattered = ray(rec.p, reflected + fuzz*random_in_unit_sphere());

            return (dot(scattered.direction(), rec.normal) > 0);
        #else
        
            // original "metal" scattering concept goes from perfect mirror
            // to a very close lambertian approximation. (probs a bug in my code)
            vec3 reflected = reflect(
                    unit_vector(r_in.d()), fuzzy_norm( r_in.d(), rec.normal, fuzz )
                );
            scattered = ray(rec.p, reflected);
            return true;
        #endif

    }

    float fuzz;
};

double schlick(double cosine, double ref_idx) {
    auto r0 = (1-ref_idx) / (1+ref_idx);
    r0 = r0*r0;
    return r0 + (1-r0)*pow((1 - cosine),5);
}

class dielectric : public material {
    public:
        dielectric(double ri, vec3 a=vec3(1,1,1)) : ref_idx(ri) { albedo = a; }

        virtual bool scatter(
            const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered
        ) const {
            attenuation = albedo; //vec3(1.0, 1.0, 1.0);
            tReal etai_over_etat = (rec.front_face) ? (1.0 / ref_idx) : (ref_idx);

            vec3 unit_direction = unit_vector(r_in.direction());
            tReal cos_theta = ffmin(dot(-unit_direction, rec.normal), 1.0);
            tReal sin_theta = sqrt(1.0 - cos_theta*cos_theta);
            if (etai_over_etat * sin_theta > 1.0 ) {
                vec3 reflected = reflect(unit_direction, rec.normal);
                scattered = ray(rec.p, reflected);
                return true;
            }
            tReal reflect_prob = schlick(cos_theta, etai_over_etat);
            if (random_double() < reflect_prob)
            {
                vec3 reflected = reflect(unit_direction, rec.normal);
                scattered = ray(rec.p, reflected);
                return true;
            }
            vec3 refracted = refract(unit_direction, rec.normal, etai_over_etat);
            scattered = ray(rec.p, refracted);
            return true;
        }

    public:
        tReal ref_idx;
};

vec3 ray_color(const ray& r, const hittable& world, int depth) {
    hit_record rec;
    if (world.hit(r, 0.001, infinity, rec)) {
        // If we've exceeded the ray bounce limit, no more light is gathered.
        if (depth < 1)
            return rec.mat_ptr->albedo;
        ray scattered;
        vec3 attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth-1);
        return rec.mat_ptr->albedo;
    }
    return sky_color(r.d());
}

#endif
