//
//  material.h
//  lvr
//
//  Created by Remi Palandri on 23/03/15.
//  Copyright (c) 2015 tuxer. All rights reserved.
//

#ifndef __lvr__material__
#define __lvr__material__

#include <iostream>
#include <map>
#include <string>
#include <list>
#include "matrix4.hpp"
#include "logger.hpp"
#include "vec3f.hpp"
#include "texture.hpp"

class Material {
public:
    Material(); //default material constructor
    
    Vec3f ambient;
    Vec3f diffuse;
    Vec3f specular;
    Texture *specularTexture;
    Texture *diffuseTexture;
    Texture *ambientTexture;
    float opacity;
    float specularDensity;
    int specularExponent;
};

#endif /* defined(__lvr__material__) */
