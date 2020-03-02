#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
    public:
        ray(const vec3& origin=vec3(0,0,0), const vec3& direc=vec3(0,0,0))
             : orig(origin), dir(direc)
        {}
            
    vec3 origin() const { return orig; }
    vec3 direction() const { return dir; }
    vec3 o() const { return orig; }
    vec3 d() const { return dir; }

    vec3 at(tReal t) const { return orig + t*dir; }
    
    vec3 orig, dir;
};

#endif
