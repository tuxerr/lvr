#ifndef DEF_UNIFORMBLOCK
#define DEF_UNIFORMBLOCK

#include <iostream>
#include <string>
#include <map>
#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>
#include "matrix4.hpp"
#include "vec3f.hpp"
#include "vec2f.hpp"
#include "logger.hpp"

class UniformBlock {
public:
    UniformBlock(std::string name,int attachpoint);
    UniformBlock(std::string name,std::string attach_name, int attachpoint);
    void create();
    void destroy();
    int get_attach_point();
    void bind_to_attach_point(GLuint program_id);
    std::string get_name();
    std::string get_attach_name();
    void set_value(bool val,std::string sub_name);
    void set_value(int val,std::string sub_name);
    void set_value(float val,std::string sub_name);
    void set_value(Vec3f &val,std::string sub_name);
    void set_value(Vec2f &val,std::string sub_name);
    void set_value(Matrix4 &val,std::string sub_name);
    void bind();
    void unbind();
    GLuint get_ubo();
    void print_contents();

private:
    GLint get_value_from_pname(std::string sub_name,GLenum pname);
    GLint get_offset(std::string sub_name);

    std::string complete_name;
    std::string attach_name; /* name to attach to the shader */
    int size;
    bool iscreated;
    bool isbinded;
    int attachpoint;
    GLuint ubo;
    GLuint program_id;
    GLuint ubo_loc_in_program;
    std::map<std::string,GLint> offsets;
    std::map<std::string,GLuint> matrix_strides;
};

#endif
