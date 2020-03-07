/* -- hyperparams.h - 2020 Mar 5 - by dafhi

        techs

    1.  anti-aliased dots.  size reduced over time
    2.  pixels.             rgb (uint) activity gets extra attention

*/

#ifndef HYPERPARAMS_H
#define HYPERPARAMS_H

void importance_map(int frame, int update_modulus = 1) {
    if (frame % update_modulus == 0) {
        activ_max = 0;
        for (int j = gh; --j > 0;) {
            framebuffer_scanline(j)
            for (int i = 0; i++ < wm;) {
                int temp = sum[srci+i].gamma();
                sum[srci+i].calc_activ(temp);
                sum[srci+i].colp = temp;
                activ_max = ffmax(activ_max, sum[srci+i].activ);
                p32[desi+i] = temp;
            }
        }
        activ_max = (activ_max == 0) ? 1 : 1 / activ_max;
        for (int i = 0; i++ < gw*gh-1;) sum[i].imap = sum[i].activ * activ_max;
    }
}

#define frame_drawdots\
    std::cerr << ".. Dots ";\
    for (int k = 0; k <= dots; ++k) {\
        float u = rnd;\
        float v = rnd;\
        float i = u * gw;\
        float j = v * gh;\
        ray r = cam.get_ray(u, v);\
        vec3 color = ray_color(r, world, max_depth);\
        aadot::draw(i,j,propix(color,dot_strength),rad,slope);\
    }\
    importance_map(frame, 1);\
    propix_frame(scaled, bool_gamma);\
    dot_dilution *= .987;

bool draw_some_dots(int frame, camera cam, hittable_list world, int max_depth, bool scaled=false) {
    static double dot_dilution = .98;
    int dots = .4 * (gw * gh) / (pi * rad * rad);
    float slope = 1 / rad;
    float dot_strength = 1.5*(1 - dot_dilution);
    if (rad > .7071) { frame_drawdots; rad *= .89; return true; } rad = .7071;
    if (dot_dilution > .6) { frame_drawdots; return true; }
    return false;
}

// + .5 eliminates blurriness from aa dots crossover which suggests problem with

// "off by one" in the camera class, or
// problem with my dots

#define first_ray\
    u = (i + rnd) / (gw + .5);\
    v = (j + rnd) / (gh + .5);\
    r = cam.get_ray(u, v);\
    samps++;

void draw_some_pixels(int frame, camera cam, hittable_list world, int max_depth, bool scaled = false) {
    std::cerr << ".. pixels ";
    const int   strat = 3;
    //const float enforced_rate = 1 / strat;
    for (int j = gh; --j >= 0;) {
        framebuffer_scanline(j)
        for (int i = 0; i < gw; ++i) {
            ray         r;
            float       u, v, s=rnd;
            int         samps=0;
            if (s < .002) {
                first_ray
                auto color = ray_color(r, world, max_depth);
                write_pixel(color, i);
            } else if (s >= .5) {
                first_ray
                auto color = ray_color(r, world, max_depth);
                for (int k=1; k++ < sum[srci+i].imap * 10;) {
                    first_ray
                    color += ray_color(r, world, max_depth);
                }
                write_pixel(color, i, samps);
            }
        }
        even_more_framebu___you_get_the_point(j, update_modulus, bool_gamma)
    }
    importance_map(frame);
}

void frame_hyperparams(int frame, camera cam, hittable_list world, int max_depth, bool scaled = false){
    initialize_profield
    update_modulus = gh;
    bool_gamma = true;
    if ( !draw_some_dots(frame, cam, world, max_depth, scaled) ) {
        draw_some_pixels(frame, cam, world, max_depth, scaled);
    }
}

/*
        std::cout << " " << dot_dilution;\
        std::cout << " " << update_modulus << " ";\
                sum[(int)i + (int)j*pitchBy] = color;\
        } else {\
        int dots = .52 * (gw * gh) / (pi * rad * rad);
*/

#endif