#include "object.hpp"
#include "octree.hpp"

inline int number_of_elements(Object_Attribs a) {
    switch(a) {
        case OBJECT_ATTRIB_VERTEX:
            return 3;
            break;
            
        case OBJECT_ATTRIB_COLOR:
            return 3;
            break;
    
        case OBJECT_ATTRIB_TEXTURE:
            return 2;
            break;
            
        case OBJECT_ATTRIB_NORMAL:
            return 3;
            break;
            
        case OBJECT_NONE:
            return 0;
            break;
    }
    return -1;
}

Object::Object(Octree *tree) : 
    has_been_drawn(false),
    ena_colors(true),
    ena_textures(true),
    ena_draw(true),
    has_normals(true),
    obj_draw_mode(OBJECT_DRAW_TRIANGLES),
    program_name("forward_instanced"),
    modelview_changed(true),
    tree(tree),
    bounding_sphere_size(0),
    bounding_scale_factor(1)
{
    glGenVertexArrays(1, &vao); // gen object-wide VAO linking available attribs to our VBO
    obj_modelview.identity();
}

void Object::destroy() {
    // destroy all subparts VBOs
    vbo->destroy();
    ibo_triangles->destroy();
    
}

int Object::new_part(Material *mat, int indexCount) {
    int previousIndexCount = 0;
    for(ObjectPart &part : parts) {
        previousIndexCount+=part.indexCount;
    }
    ObjectPart part = {previousIndexCount,indexCount,mat};
    parts.push_back(part);
    return (int)parts.size()-1;
}

void Object::update_vertex_buffer(void *data,int size,Object_Attribs attrib) {
    int offset = 0, stride = 0;
    bool found = false;
    for(Object_Attribs a : attribs) {
        int sizeIncr = number_of_elements(a)*sizeof(float);
        stride += sizeIncr;
        if(!found) {
            offset += sizeIncr;
        }
        
        if(a==attrib) {
            found = true;
        }
    }
    
    
    
    
}

void Object::calculate_bounding_sphere() {
    int total_weight=0;
    bounding_sphere_size=0;
    for(unsigned int i=0;i<parts.size();i++) {
        total_weight+=parts[i][0].bounding_sphere_weight;
        bounding_sphere_size+=(parts[i][0].bounding_sphere_weight*parts[i][0].bounding_sphere_size);
    }
    bounding_sphere_size/=total_weight;
}

float Object::bounding_size() {
    return bounding_sphere_size*bounding_scale_factor;
}


void Object::enable_color(bool color) {
    ena_colors=color;
}

void Object::enable_textures(bool textures) {
    ena_textures=textures;
}

void Object::set_enable_draw(bool draw) {
    ena_draw=draw;
}

bool Object::enable_draw() {
    return ena_draw;
}

void Object::set_draw_mode(Object_Draw_Modes draw_mode) {
    obj_draw_mode=draw_mode;
    for(unsigned int i=0;i<parts.size();i++) {
        for(unsigned int j=0;j<parts[i].size();j++) {
            switch(draw_mode) {
                case OBJECT_DRAW_LINES:
                    glBindVertexArray(parts[i][j].vao);
                    parts[i][j].ibo_lines.bind();
                    glBindVertexArray(0);
                    break;
                    
                case OBJECT_DRAW_TRIANGLES:
                    glBindVertexArray(parts[i][j].vao);
                    parts[i][j].ibo_triangles.bind();
                    glBindVertexArray(0);
                    break;
                    
                case OBJECT_DRAW_PATCHES:
                    glBindVertexArray(parts[i][j].vao);
                    parts[i][j].ibo_quads.bind();
                    glBindVertexArray(0);
                    break;
            }
        }
    }
}

Matrix4 &Object::modelview_matrix() {
    return obj_modelview;
}

Matrix4 &Object::projection_modelview_matrix() {
    return projection_modelview;
}

Matrix4 &Object::normal_matrix() {
    return normal_mat;
}

std::string Object::get_program() {
    return program_name;
}

void Object::set_program(std::string name) {
    program_name=name;
}

void Object::reset_lod_to_draw() {
    lod_to_draw=-1;
}

void Object::draw(float distance_from_camera) {
    if(lod_to_draw==-1) {
        for(unsigned int i=0;i<parts[0].size();i++) {
            if(parts[0][i].lodmindist<=distance_from_camera) {
                lod_to_draw=i;
            } else {
                break;
            }
        }
    }         
    int lod=lod_to_draw;
    
    for(unsigned int i=0;i<parts.size();i++) {
        glBindVertexArray(parts[i][lod].vao);

        if(obj_draw_mode==OBJECT_DRAW_LINES && parts[i][lod].ibo_lines.size()>0) {
            glDrawElements(GL_LINES,parts[i][lod].ibo_lines.size()/parts[i][lod].ibo_lines.element_size(),parts[i][lod].ibo_lines.element_type(),0);
        } else if(obj_draw_mode==OBJECT_DRAW_PATCHES && parts[i][lod].ibo_quads.size()>0) {
            // patches and quads share the same VBOs, since GL_PATCH_VERTICES is 4 (patches are just special quads)
            glDrawElements(GL_PATCHES,parts[i][lod].ibo_quads.size()/parts[i][lod].ibo_quads.element_size(),parts[i][lod].ibo_quads.element_type(),0);
        } else if(obj_draw_mode==OBJECT_DRAW_TRIANGLES && parts[i][lod].ibo_triangles.size()>0) {
            parts[i][lod].ibo_triangles.bind();
            glDrawElements(GL_TRIANGLES,parts[i][lod].ibo_triangles.size()/parts[i][lod].ibo_triangles.element_size(),parts[i][lod].ibo_triangles.element_type(),0);
        }
        
        glBindVertexArray(0);
    }

}

void Object::translate(float x, float y, float z) {
    obj_modelview.translate(x,y,z);
    modelview_changed=true;
    if(tree!=NULL) {
        tree->delete_object(this);
        tree->add_object(this);
    }
}

void Object::set_pos(Vec3<float> pos) {
    set_pos(pos.x,pos.y,pos.z);
}

void Object::set_pos(float x, float y, float z) {
    Vec3<float> pos = position();
    Vec3<float> destination = Vec3<float>(x,y,z);
    Vec3<float> translation = destination-pos;
    translate(translation.x,translation.y,translation.z);
}

void Object::scale(float x, float y, float z) {
    obj_modelview.scale(x,y,z);
    modelview_changed=true;
    bounding_scale_factor*=maxf(maxf(x,y),z);
    if(tree!=NULL) {
        tree->delete_object(this);
        tree->add_object(this);
    }
}

void Object::reset_modelview() {
    obj_modelview.identity();
}

void Object::rotate(float angle,float x, float y, float z) {
    obj_modelview.rotate(angle,x,y,z);
    modelview_changed=true;
}

bool Object::need_to_update_matrices() {
    return modelview_changed;
}

void Object::update_matrices(Matrix4 *perspective,Matrix4 *camera) {
    if(camera!=NULL) {
        total_modelview = (*camera)*obj_modelview;

        if(modelview_changed && has_normals) {
            normal_mat = obj_modelview; 
            normal_mat.invert();
            normal_mat.transpose();
        } 

        if(perspective!=NULL) {
            projection_modelview = (*perspective)*total_modelview;
        }

    }
    modelview_changed=false;
}

Vec3f Object::position() {
    return Vec3f(obj_modelview.val[3],obj_modelview.val[7],obj_modelview.val[11]);
}
