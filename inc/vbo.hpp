#ifndef DEF_VBO
#define DEF_VBO

#include <iostream>
//#include <GL/glew.h>
#define GLFW_INCLUDE_GLCOREARB
//#include <GLFW/glfw3.h>
#include <string.h>
#include "shader_program.hpp"
#include "logger.hpp"

class VBO {
public:
    VBO(GLenum target,GLenum mode,GLenum element_type,GLuint vao);
    VBO(GLenum target,GLenum mode,GLenum element_type,GLuint vao,Shader_Attribs attrib);
    ~VBO();
    void create();
    bool iscreated();
    void destroy();
    void bind();
    void unbind();
    GLuint id();
    int size();
    int element_size();
    GLenum element_type();
    void update(void *data,int size);
    void updateWithStride(void *data, int size, int elemSize, int offset, int stride);
    void print_contents();

private:
    GLuint vao;
    GLuint vbo;
    GLenum vbo_type;
    GLenum access_mode;
    GLsizei vbo_size;
    GLsizei vbo_capacity;
    GLint vbo_element_size;
    GLenum vbo_element_type;
    bool created;
};

#endif
