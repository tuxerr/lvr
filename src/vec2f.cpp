#include "vec2f.hpp"

Vec2f::Vec2f(float x,float y) : x(x), y(y) {
}

float Vec2f::norm() {
    return sqrt(x*x+y*y);
}

void Vec2f::normalize() {
    float val=norm();
    if(val!=0) {
        x/=val;
        y/=val;
    }
}

Vec2f Vec2f::operator+(Vec2f n) {
    n.x+=x;
    n.y+=y;
    return n;
}

Vec2f Vec2f::operator-(Vec2f n) {
    n.x-=x;
    n.y-=y;
    return n;
}
