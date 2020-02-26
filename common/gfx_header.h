#ifndef GFX_HEADER_H
#define GFX_HEADER_H

/* -- Dev-C++     -lmingw32 -lSDL2main -lSDL2

    gfx_header.h

*/

#include <limits>
//#include <cstdlib>
//#include <memory>

#define tReal   float

// Usings

//using std::shared_ptr;
//using std::make_shared;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double random_double() {
    // Returns a random real in [0,1).
    return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max-min) * random_double();
}

#define rnd random_double()

inline tReal degrees_to_radians(tReal degrees) {
    return degrees * pi / 180;
}

#define uint    unsigned int

#endif// -------- HEADER_H

