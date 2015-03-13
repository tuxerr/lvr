#ifndef DEF_VEC2
#define DEF_VEC2

#include <math.h>

class Vec2f {
public:
    Vec2f(float = 0,float = 0);
    float x;
    float y;
    float norm();
    void normalize();
    Vec2f operator+(Vec2f n);
    Vec2f operator-(Vec2f n);
private:
};

#endif
