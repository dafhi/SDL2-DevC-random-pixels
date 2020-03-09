#ifndef RTWEEKEND_H
#define RTWEEKEND_H
//==============================================================================================
// To the extent possible under law, the author(s) have dedicated all copyright and related and
// neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy (see file COPYING.txt) of the CC0 Public Domain Dedication
// along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
//==============================================================================================

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>

#include "gfx_header.h"

// Usings

using std::shared_ptr;
using std::make_shared;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline double ffmin(double a, double b) { return a <= b ? a : b; }
inline double ffmax(double a, double b) { return a >= b ? a : b; }

inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

inline double drand() {
    // Rolled my own PRNG.  2019 Jan 20  - dafhi (somewhere around that time)
    // nearly-flat distribution (exactly 2 values are off the average by 1)
	static uint a = 0, b = 0;
	const uint max = std::numeric_limits<uint>::max();
	a *= a;
	a ^= b;
	b += 1; // 1,5,9,etc. will hit all possible values.  3,7,11 will miss half
	return (double)a / max;
}

inline double random_double() {
    #if 1
    return drand();
    #else
    return rand() / (RAND_MAX + 1.0);
    #endif
}

inline double random_double(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max-min)*random_double();
}

inline int random_int(int min, int max) {
    // Returns a random integer in [min,max].
    return static_cast<int>(random_double(min, max+1));
}

#define rnd     random_double()

// Common Headers

#include "ray.h"

vec3 sky_color(const vec3& ray_d) {
    auto t = (unit_vector(ray_d).y() + 1)/2;
    return (1.0-t)*vec3(1.0,1.0,1.0) + t*vec3(0.5,0.7,1.0);
}

#endif
