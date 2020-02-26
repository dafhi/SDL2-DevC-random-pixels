/* -- vec3.h

    referended from "Ray Tracing in one Weekend" by Peter Shirley

*/

#ifndef VEC3_H
#define VEC3_H

#include <iostream>
#include <cmath>

#include "gfx_header.h"

class vec3 {
    public:
        vec3() : e{0,0,0} {}
        vec3(tReal e0, tReal e1, tReal e2) : e{e0, e1, e2} {}

        tReal x() const { return e[0]; }
        tReal y() const { return e[1]; }
        tReal z() const { return e[2]; }

        vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
        tReal operator[](int i) const { return e[i]; }
        tReal& operator[](int i) { return e[i]; }

        vec3& operator+=(const vec3 &v) {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;
        }

        vec3& operator*=(const tReal t) {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }

        vec3& operator/=(const tReal t) {
            return *this *= 1/t;
        }

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

#endif

