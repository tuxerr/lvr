#ifndef DEF_OBJECT
#define DEF_OBJECT

#include <iostream>
#include <map>
#include <string>
#include <list>
//#include <GL/glew.h>
#define GLFW_INCLUDE_GLCOREARB
//#include <GLFW/glfw3.h>
#include "vbo.hpp"
#include "matrix4.hpp"
#include "utils.hpp"
#include "logger.hpp"
#include "material.hpp"

enum Object_Attribs {
    OBJECT_ATTRIB_VERTEX, //3
    OBJECT_ATTRIB_COLOR, //3
    OBJECT_ATTRIB_TEXTURE, //2
    OBJECT_ATTRIB_NORMAL, //3
    OBJECT_NONE
};

inline int number_of_elements(Object_Attribs a);

class Octree;

#define BUFFER_OFFSET(a) ((char*)NULL + (a))

typedef enum Object_Draw_Modes {
    OBJECT_DRAW_TRIANGLES = GL_TRIANGLES, OBJECT_DRAW_LINES = GL_LINES, OBJECT_DRAW_PATCHES = GL_PATCHES, OBJECT_DRAW_NONE = GL_NONE
} Object_Draw_Modes;

typedef struct ObjectPart {
    int firstIndexOffset;
    int indexCount;
    Material *mat;
} ObjectPart;

class Object {
public:
    Object(Octree *tree);
    void destroy();
    int new_part(Material *mat, int indexCount);
    void update_index_buffer(void *data,int size);
    void update_vertex_buffer(void *data,int size,Object_Attribs attrib);
    float bounding_size();
    bool need_to_update_matrices();
    void update_matrices(Matrix4 *perspective,Matrix4 *camera);
    void enable_color(bool color);
    void enable_textures(bool textures);
    void set_enable_draw(bool draw);
    bool enable_draw();
    void set_draw_mode(Object_Draw_Modes draw_mode);
    Matrix4 &modelview_matrix();
    Matrix4 &projection_modelview_matrix();
    Matrix4 &normal_matrix();
    std::string get_program();
    void set_program(std::string name);
    void draw(float distance_from_camera);
    void translate(float x, float y, float z);
    void scale(float x, float y, float z);
    void rotate(float angle,float x, float y, float z);
    void reset_modelview();
    void set_pos(float x, float y, float z);
    void set_pos(Vec3<float> pos);
    Vec3<float> position();

    bool has_been_drawn;
    
private:
    std::vector<ObjectPart> parts; /* parts[PART_NB] */
    bool ena_colors;
    bool ena_textures;
    bool ena_draw;
    bool has_normals;
    Object_Draw_Modes obj_draw_mode;
    std::string program_name;
    Matrix4 obj_modelview;
    bool modelview_changed;
    Matrix4 total_modelview;
    Matrix4 projection_modelview;
    Matrix4 normal_mat;
    Octree *tree;

    float bounding_sphere_size;
    float bounding_scale_factor;
    void calculate_bounding_sphere();

    VBO vbo;
    VBO ibo_triangles;
    GLuint vao;
    
    std::vector<Object_Attribs> attribs;
};

#endif
