#ifndef DEF_VEC3
#define DEF_VEC3

#include <math.h>

class Vec3f {
public:
    Vec3f(float = 0,float = 0,float = 0);
    float x;
    float y;
    float z;
    float norm();
    Vec3f normalize();
    Vec3f cross(Vec3f n);
    float scalar(Vec3f n);
    Vec3f operator+(Vec3f n);
    Vec3f operator-(Vec3f n);
    Vec3f operator*(Vec3f n);
    Vec3f operator*(float n);
private:
};

#endif
