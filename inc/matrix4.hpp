#ifndef DEF_MATRIX4
#define DEF_MATRIX4

#include <iostream>
#include <vector>
#include <math.h>
#include "vec3f.hpp"
#include "logger.hpp"

class Matrix4 {
public:
    Matrix4();
    Matrix4(float *val);
    Matrix4(const Matrix4 &mat);
    void clear();
    void identity();
    void print();
    float get_val(int i);
    void set_val(int i,float f);
    float* adress();
    void transpose();
    void invert();
    Matrix4 operator*(const Matrix4 &mat);
    Vec3f operator*(Vec3f vector);
    void translate(float x, float y, float z);
    void scale(float x, float y, float z);
    void rotate(float angle,float x, float y, float z);
    void perspective(float fovx,float near,float far,float ratio);    
    void perspective_ortho(float width,float near,float far,float ratio);
    void camera(Vec3f pos,Vec3f direction,Vec3f up_vector);

    float val[16];
};

#endif
