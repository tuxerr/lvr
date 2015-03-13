#include "vec3f.hpp"

Vec3f::Vec3f(float x,float y,float z) : x(x), y(y), z(z) {
}

float Vec3f::norm() {
    return sqrt(x*x+y*y+z*z);
}

Vec3f Vec3f::normalize() {
    float val=norm();
    if(val!=0) {
        x/=val;
        y/=val;
        z/=val;
    }
    return Vec3f(x,y,z);
}

Vec3f Vec3f::operator+(Vec3f n) {
    n.x+=x;
    n.y+=y;
    n.z+=z;
    return n;
}

Vec3f Vec3f::operator-(Vec3f n) {
    Vec3f res;
    res.x=x-n.x;
    res.y=y-n.y;
    res.z=z-n.z;
    return res;
}

// vectorial product
Vec3f Vec3f::operator*(Vec3f n) {
    Vec3f res;
    res.x=(y*n.z-z*n.y);
    res.y=(z*n.x-x*n.z);
    res.z=(x*n.y-y*n.x);
    return res;
}

Vec3f Vec3f::operator*(float n) {
    Vec3f res;
    res.x=x*n;
    res.y=y*n;
    res.z=z*n;
    return res;
}

//cross product
Vec3f Vec3f::cross(Vec3f n) {
    Vec3f res;
    res.x=y*n.z-z*n.y;
    res.y=z*n.x-x*n.z;
    res.z=x*n.y-y*n.x;
    return res;
}

//cross product
float Vec3f::scalar(Vec3f n) {
    return n.x*x+n.y*y+n.z*z;
}
