/* -- vec3.h

    tinkered vector class from "Ray Tracing in one Weekend" by Peter Shirley

*/

#ifndef VEC3_H
#define VEC3_H

#include "gfx_header.h" // cmath, general.h -> random_double

#include <iostream>

class vec3 {
    public:
        vec3() : e{0,0,0} {}
        vec3(const tReal e0, const tReal e1, const tReal e2) : e{e0, e1, e2} {}
        vec3(const vec3& a) : e{a[0], a[1], a[2]} {}
        vec3(vec3& a) : e{a[0], a[1], a[2]} {}
//        operator uint() const { return rgb_f(e[0], e[1], e[2]); }

//        vec3 gamma() const { return vec3(sqrt(e[0]),sqrt(e[1]),sqrt(e[2])); }

        tReal x() const { return e[0]; }
        tReal y() const { return e[1]; }
        tReal z() const { return e[2]; }

        vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
        tReal operator[](int i) const { return e[i]; }
        //tReal& operator[](int i) { return e[i]; }

        vec3& operator+=(const vec3 &v) {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;
        }
        
#if 1
        vec3& operator-=(const vec3 &v) {
            e[0] -= v.e[0];
            e[1] -= v.e[1];
            e[2] -= v.e[2];
            return *this;
        }
#endif

        vec3& operator*=(const tReal t) {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }
        
#if 0
        vec3& operator/=(const tReal t) {
            return *this *= 1/t;
        }
#endif
        tReal length() const {
            return sqrt(length_squared());
        }

        tReal length_squared() const {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }

        void write_color(std::ostream &out) {
            // Write the translated [0,255] value of each color component.
            out << static_cast<int>(255.999 * e[0]) << ' '
                << static_cast<int>(255.999 * e[1]) << ' '
                << static_cast<int>(255.999 * e[2]) << '\n';
        }

    inline static vec3 random() {
        return vec3(rnd, rnd, rnd);
    }

    inline static vec3 random(tReal min, tReal max) {
        return vec3(random_double(min,max), random_double(min,max), random_double(min,max));
    }

    public:
        tReal e[3];
};

// vec3 Utility Functions

inline std::ostream& operator<<(std::ostream &out, const vec3 &v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(tReal t, const vec3 &v) {
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline vec3 operator*(const vec3 &v, tReal t) {
    return t * v;
}

inline vec3 operator/(vec3 v, tReal t) {
    return (1/t) * v;
}

inline tReal dot(const vec3 &u, const vec3 &v) {
    return u.e[0] * v.e[0]
         + u.e[1] * v.e[1]
         + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3 &u, const vec3 &v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector(vec3 v) {
    return v / v.length();
}

vec3 random_in_unit_sphere() {
    while (true) {
        auto p = vec3::random(-1,1);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

vec3 random_unit_vector() {
    auto a = random_double(0, 2*pi);
    auto z = random_double(-1, 1);
    auto r = sqrt(1 - z*z);
    return vec3(r*cos(a), r*sin(a), z);
}

vec3 random_in_hemisphere(const vec3& normal) {
    vec3 in_unit_sphere = random_in_unit_sphere();
    if (dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return in_unit_sphere;
    else
        return -in_unit_sphere;
}

vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2*dot(v,n)*n;
}

vec3 refract(const vec3& uv, const vec3& n, tReal etai_over_etat) {
    auto cos_theta = dot(-uv, n);
    vec3 r_out_parallel =  etai_over_etat * (uv + cos_theta*n);
    vec3 r_out_perp = -sqrt(1.0 - r_out_parallel.length_squared()) * n;
    return r_out_parallel + r_out_perp;
}

vec3 random_in_unit_disk() {
    while (true) {
        auto p = vec3(random_double(-1,1), random_double(-1,1), 0);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

vec3 rodrigues_rot( vec3 rd, vec3 axis, float angle) {

    float cosa = cos(angle);
    
    return (1-cosa) * ( axis.x()*rd.x() + axis.y()*rd.y() + axis.z()*rd.z() ) *
        axis + cosa*rd + sin(angle) *
        vec3(
            axis.y()*rd.z()-axis.z()*rd.y(),
            axis.z()*rd.x()-axis.x()*rd.z(),
            axis.x()*rd.y()-axis.y()*rd.x()
        );
}

vec3 fuzzy_norm( vec3 rd, vec3 surf_n, float k) {
    rd = unit_vector(rd);

    const vec3 vtemp =
        rodrigues_rot(surf_n, cross(surf_n, rd), -acos(-dot(surf_n, rd)) * k / 2 );

    const float a = sqrt(2);
    return unit_vector(vtemp * a + random_in_unit_sphere() * k);
}

#endif

