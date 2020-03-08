/*  general.h - 2020 Feb 20 - by dafhi

*/

#ifndef GENERAL_H
#define GENERAL_H

#include <limits>

#define uint    unsigned int
#define uchar   unsigned char

#define tReal   float

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

#define rnd     random_double()

#if 0
inline double random_double() {
    // Returns a random real in [0,1).
    #if 1
    return drand();
    #else
    return rand() / (RAND_MAX + 1.0);
    #endif
}

inline double random_double(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max-min) * rnd;
}
#endif

//#define flr(x)  (2*((x)/2)-.5)

//inline tReal clamp(const tReal in, const tReal min = 0, const tReal max = 1) {
//    return in < min ? min :  in > max ? max : in;
//}

//#define ffmax(t,c)  (t < c) ? c : t
//#define ffmin(t,c)  (t > c) ? c : t
//inline double ffmin(double a, double b) { return a <= b ? a : b; }
//inline double ffmax(double a, double b) { return a >= b ? a : b; }

#endif
