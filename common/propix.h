/*  -- Dev-C++     -lmingw32 -lSDL2main -lSDL2

    progressive pixel class and SDL2 encapsulation defines
    2020 Feb 26 - by dafhi
    
*/

#ifndef PROPIX_H
#define PROPIX_H

#include "ray.h"

    #define propix progressive_pixel

class progressive_pixel {
      public:
          
    propix(tReal x=0, tReal y=0, tReal z=0, tReal w=0) { v=vec3(x,y,z); iter = w;}
    propix(const vec3& q, tReal w=1) {v = q; iter = w;}
    propix(const propix& q, tReal w=1) {v = q.v; iter = w;}

    operator vec3() { return v / iter; }
    const tReal operator[](int i) const { return v[i]; }

    // non-gamma
    operator uint() const { const tReal r = 1/iter; return rgb_i(v[0]*r, v[1]*r, v[2]*r); }
    //operator uint() const { const tReal r = 1/iter; return rgb_f(v[0]*r, v[1]*r, v[2]*r); }
    uint gamma() const { const tReal r = 1/iter; return rgb_f(v[0]*r, v[1]*r, v[2]*r); }

    propix& operator+=(const propix &u) {
        v += u.v;
        iter += u.iter;
        return *this;
    }

    vec3    v;
    tReal   iter;
    uint    colp;
    tReal   activ;
};


inline std::ostream& operator<<(std::ostream &out, const propix &v) {
    return out << v.v[0] << ' ' << v.v[1] << ' ' << v.v[2] << ' ' << v.v[3];
}

inline const propix operator-(const propix& u, const propix& v) {
    return propix(u[0]-v[0], u[1]-v[1], u[2]-v[2], u.iter);
}

inline propix operator*(tReal const t, const propix &v) {
    return propix(t*v[0], t*v[1], t*v[2], v.iter);
}

inline propix operator*(const propix &v, tReal const t) {
    return t * v;
}

inline propix operator/(propix &v, tReal t) {
    return (1/t) * v;
}

#endif // --- 
