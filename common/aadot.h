/* -- 

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
        int y0 = ffmax(y-rad, 0);
        int y1 = ffmin(y+rad+.5, hm);

        x += .5;
        int x0 = ffmax(x-rad, 0);
        int x1 = ffmin(x+rad+.5, wm);

        float dy = (y0-y)*slope;
        const float dxleft = (x0-x)*slope;

        const float cone_h = slope*(rad+.25);     //pre-inverted, imagined as cone \/
        const float coneSq = cone_h*cone_h;      //avoid sqr() at blit corners
        const float sq = (cone_h-1)*(cone_h-1);  //avoid sqr() in dot center at max brightness
        
        #if 0
        std::cout << coneSq << " ";
        std::cout << sq;
        if (x1 > wm ) std::cout << "X w";
        if (y1 > hm ) std::cout << "Y h";
        if (x1 < 0 ) std::cout << "X -1";
        if (y1 < 0 ) std::cout << "Y -1";
        #endif
        
        for (int j = y0; j <= y1; j++) {
            float dx = dxleft;
            const float dySq = dy*dy;
            for (int i = x0 + j*pitchBy; i <= x1 + j*pitchBy; i++) {
                float salpha = dx*dx+dySq;
                if (salpha<sq) {
                    gsum[i] += propix(col*col.iter, col.iter);
                    //p32[i] = gsum[i];
                } else if ( salpha <= coneSq) {
                    
                    #if 0
                    salpha = col.iter * (cone_h-(salpha));
                    #else
                    salpha = col.iter * (cone_h-sqrt(salpha));
                    #endif
                    gsum[i] += propix(col * salpha, salpha);
                    //p32[i] = gsum[i];
                }
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

