/*  general.h - 2020 Feb 20 - by dafhi

*/

#ifndef GENERAL_H
#define GENERAL_H

#include <cstdlib>

#define rnd     random_double()

inline double rnd {
    // Returns a random real in [0,1).
    return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max-min) * rnd;
}

#define flr(x)  (2*((x)/2)-.5)

#define uint    unsigned int
#define uchar   unsigned char

#define tReal   float

inline tReal clamp(const tReal in, const tReal min = 0, const tReal max = 1) {
    return in < min ? min :  in > max ? max : in;
}

#define ffmax(t,c)  (t < c) ? c : t
#define ffmin(t,c)  (t > c) ? c : t
//inline double ffmin(double a, double b) { return a <= b ? a : b; }
//inline double ffmax(double a, double b) { return a >= b ? a : b; }

#endif
