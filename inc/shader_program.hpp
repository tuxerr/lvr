#ifndef DEF_SHADER_PROGRAM
#define DEF_SHADER_PROGRAM

#include <iostream>
#include <map>
#include <list>
#include <string>
#define GLFW_INCLUDE_GLCOREARB
//#include <GLFW/glfw3.h>
#include <stdio.h>
#include <string.h>
#include "matrix4.hpp"
#include "uniform.hpp"
#include "uniformblock.hpp"

class Program {
public:
    Program();
    ~Program();
    void load_shaders(const char *vertex_shader_path,const char *fragment_shader_path,const char *tessellation_control_shader_path,const char *tessellation_evaluator_shader_path,const char *geometry_shader_path);
    GLuint compile_shader(const char *path,GLenum shader_type);
    void subscribe_to_uniform(Uniform *uni);
    void subscribe_to_uniformblock(UniformBlock *uni);
    void use();
    void bind_texture(Texture* tex);
    void unuse();
    GLuint id();
    bool isBinded();
    
private:
    GLuint program_id;
    std::map<Uniform*,bool> uniforms;
    std::list<Texture*> textures;
    bool binded;
};

#endif
