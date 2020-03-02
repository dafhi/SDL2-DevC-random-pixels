#if 0
    propix& operator=(const vec3& v3) {
        v += v3;
        iter += 1;
        return *this;
    }
    progressive_pixel& operator/=(const tReal t) {
        return *this *= 1/t;
    }

    progressive_pixel& operator+=(const propix &w) {
        v+=w.v;
        //a+=w.a;
//        std::cout << w.v << ' ' << a << "\n";
        return *this;
    }

    progressive_pixel& operator-=(const propix &w) {
        v -= w.v;
        a++;
        return *this;
    }

    propix& operator+=(const vec3 &u) {
        v += u;
        iter += 1;
        return *this;
    }

#endif


    #if 0
    auto a=propix(.5,.5,.5),b=propix(1,1,.5,.5);
//    a += (b-a);
    a.add(b);
//    a += b;

    std::cout << ((uint)a & 0xFF) << "\n";
    std::cout << b;
    #endif

//    SDL_Delay(500);


class vec4 {
    public:
    vec4(float x=0, float y=0, float z=0, float w=1) : e{x,y,z,w} {}
    vec4(const vec3& q, float w=1) : e{q.e[0],q.e[1],q.e[2],w} {}
#if 0
    operator auto() {
        return vec4(e[0],e[1],e[2],e[3]) / e[3];//((a == 0) ? 1 : a);
    }
#endif
    tReal operator[](int i) const { return e[i]; }

    vec4& operator+=(const vec4 &t) {
        static const float a = 1 / t.e[3];
        e[0] += t.e[0]*a;
        e[1] += t.e[1]*a;
        e[2] += t.e[2]*a;
        e[3] ++;
        return *this;
    }
    
    vec4& operator*=(const tReal t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }
    
    tReal e[4];
};

inline std::ostream& operator<<(std::ostream &out, const vec4 &v) {
    static const tReal a = 1/v.iter;
    
    return out << v.e[0]*a << ' ' << v.e[1]*a << ' ' << v.e[2]*a;
}

inline vec4 operator-(const vec4& u, const vec4& v) {
    static const float a = 1 / t.e[3];
    return vec4(u[0]-v[0], u[1]-v[1], u[2]-v[2], u.iter);
}

inline vec4 operator*(tReal t, const vec4 &v) {
    return vec4(t*v.e[0], t*v.e[1], t*v.e[2], v.iter);
}

inline vec4 operator*(const vec4 &v, tReal t) {
    return t * v;
}

inline vec4 operator/(vec4 &v, tReal t) {
    return (1/t) * v;
}


    #if 0
    /*
    struct dot_vars{

        float   x;
        float   y;
        float   rad = .5;
        float   slope = 1;

        union {
            uint    col;
            struct {
                uchar a;
                uchar r;
                uchar g;
                uchar b;
            };
        };

    };
    */
    #endif

