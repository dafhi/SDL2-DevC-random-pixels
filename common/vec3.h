#ifndef VEC3_H
#define VEC3_H
//==============================================================================================
// Originally written in 2016 by Peter Shirley <ptrshrl@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related and
// neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy (see file COPYING.txt) of the CC0 Public Domain Dedication
// along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
//==============================================================================================

#include <iostream>
//#include <cmath>
#include "rtweekend.h"

class vec3 {
    public:
        vec3() : e{0,0,0} {}
        vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

        double x() const { return e[0]; }
        double y() const { return e[1]; }
        double z() const { return e[2]; }

        vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
        double operator[](int i) const { return e[i]; }
        double& operator[](int i) { return e[i]; }

        vec3& operator+=(const vec3 &v) {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;
        }

        vec3& operator*=(const double t) {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }

        vec3& operator/=(const double t) {
            return *this *= 1/t;
        }

        double length() const {
            return sqrt(length_squared());
        }

        double length_squared() const {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }

        void write_color(std::ostream &out, int samples_per_pixel) {
            // Replace NaN component values with zero.
            // See explanation in Ray Tracing: The Rest of Your Life.
            if (e[0] != e[0]) e[0] = 0.0;
            if (e[1] != e[1]) e[1] = 0.0;
            if (e[2] != e[2]) e[2] = 0.0;

            // Divide the color total by the number of samples and gamma-correct
            // for a gamma value of 2.0.
            auto scale = 1.0 / samples_per_pixel;
            auto r = sqrt(scale * e[0]);
            auto g = sqrt(scale * e[1]);
            auto b = sqrt(scale * e[2]);

            // Write the translated [0,255] value of each color component.
            out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
                << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
                << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
        }

        inline static vec3 random() {
            return vec3(random_double(), random_double(), random_double());
        }

        inline static vec3 random(double min, double max) {
            return vec3(random_double(min,max), random_double(min,max), random_double(min,max));
        }

    public:
        double e[3];
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

inline vec3 operator*(double t, const vec3 &v) {
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline vec3 operator*(const vec3 &v, double t) {
    return t * v;
}

inline vec3 operator/(vec3 v, double t) {
    return (1/t) * v;
}

inline double dot(const vec3 &u, const vec3 &v) {
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

vec3 random_in_unit_disk() {
    while (true) {
        auto p = vec3(random_double(-1,1), random_double(-1,1), 0);
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

vec3 random_in_unit_sphere() {
    while (true) {
        auto p = vec3::random(-1,1);
        if (p.length_squared() >= 1) continue;
        return p;
    }
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

vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) {
    auto cos_theta = ffmin(dot(-uv, n), 1.0);
    vec3 r_out_parallel =  etai_over_etat * (uv + cos_theta*n);
    vec3 r_out_perp = -sqrt(1.0 - r_out_parallel.length_squared()) * n;
    return r_out_parallel + r_out_perp;
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
