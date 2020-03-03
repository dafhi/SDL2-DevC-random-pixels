#ifndef GFX_HEADER_H
#define GFX_HEADER_H

#include "general.h"

#include <cmath>

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility

inline tReal degrees_to_radians(const tReal degrees) {
    return degrees * pi / 180;
}

inline uint rgba(uchar r, uchar g, uchar b, uchar a){
   return a << 24 | r << 16 | g << 8 | b;
}

inline uint rgb(int r, int g, int b){
   return 0xFF000000 | r << 16 | g << 8 | b;
}

#define sqr255(f)   f <= 0 ? 0 : f < 1 ? 255.999 * sqrt(f) : 255
#define i255(f)   f <= 0 ? 0 : f < 1 ? 255.999 * (f) : 255

inline uint rgb_f(float r, float g, float b) {
  return rgb( sqr255(r), sqr255(g), sqr255(b) );
}

inline uint rgb_i(float r, float g, float b) {
  return rgb( i255(r), i255(g), i255(b) );
}

// 2017 Mar 26 - dafhi
#define Alpha256(back, fore, a256) \
    (\
        (   (fore & 0xff00ff) * a256 + \
            (back & 0xff00ff) * (256-a256) + 0x800080\
        ) & 0xff00ff00 | \
        (   (fore & 0x00ff00) * a256 + \
            (back & 0x00ff00) * (256-a256) + 0x008000\
        ) & 0x00ff0000 \
    ) >> 8;
    
struct image_vars {
    int w, h, pitch, *pixels;
};

#define r255    rnd * 256

#endif// -------- HEADER_H

