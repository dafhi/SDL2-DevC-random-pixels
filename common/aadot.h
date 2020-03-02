/* -- vec3.h

    referended from "Ray Tracing in one Weekend" by Peter Shirley

*/

#ifndef AADOT_H
#define AADOT_H

#include "SDL2_and_progressive_rendering.h"

namespace aadot {

    void draw(float x, float y, propix col = vec3(1,1,1), const float rad=5, float slope=1) {
        static float salpha;

        /* slope = 1 .. 1 pixel aa edge
           slope = 2 .. 1/2 pixel (sharp)
           slope = 1/rad .. max blur
           slope < 1/rad .. rendering artifact */
        
        //salpha = 1 / rad;                         // clamp prevents artifact
        //slope = slope < salpha ? salpha : slope;  //

        y += .5;
        int y0 = ffmin(y-rad, 0);
        int y1 = ffmax(y+rad+.5, hm);

        x += .5;
        int x0 = ffmin(x-rad, 0);
        int x1 = ffmax(x+rad+.5, wm);

        float dy = (y0-y)*slope;
        const float dxleft = (x0-x)*slope;

        const float cone_h = slope*(rad+.25);     //pre-inverted, imagined as cone \/
        const float coneSq = cone_h*cone_h;      //avoid sqr() at blit corners
        const float sq = (cone_h-1)*(cone_h-1);  //avoid sqr() in dot center at max brightness

        for (int j = y0; j <= y1; ++j) {
            int idx = j * pitchBy + x0;
            float dx = dxleft;
            const float dySq = dy*dy;
            for (int i = x0; i <= x1; ++i) {
                float salpha = dx*dx+dySq;
                #if 0
                #elif 1
                    if (salpha<sq) {
                        sum[idx] += propix(col*col.iter, col.iter);
                        p32[idx] = sum[idx];
                    } else if ( salpha <= coneSq) {
                        salpha = col.iter * (cone_h-sqrt(salpha));
                        sum[idx] += propix(col * salpha, salpha);
                        p32[idx] = sum[idx];
                    }
//                    std::cout << col[3] << "\n";
                #endif
                ++idx;
                dx+=slope;
            }
            dy+=slope;
        }

    }
    
    float relative_slope(float in, float radius) {
        return in / radius;
    }

}

#endif

