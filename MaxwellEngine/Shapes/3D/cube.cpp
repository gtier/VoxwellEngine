//
//  cube.cpp
//  MaxwellEngine
//
//  Created by Griffin Dunaif on 11/5/20.
//  Copyright © 2020 Griffin Dunaif. All rights reserved.
//

#include "cube.hpp"

mes::cube::cube() :
indices({
    0, 1, 3, // first triangle
    1, 2, 3,  // second triangle
   
    4, 5, 7, // first triangle
    5, 6, 7,  // second triangle
   
    8, 9, 11, // first triangle
    9, 10, 11,  // second triangle
    
    12, 13, 15,
    13, 14, 15,
    
    16, 17, 19,
    17, 18, 19,
    
    20, 21, 23,
    21, 22, 23
}),
mat(1.0f)
{
    std::vector<float>* verts_ptr = new std::vector<float>({
        // positions       // uv       // normal
        1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, // top right
        1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom right
        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom left
        0.0f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // top left
        
        // TODO fix coords
        1.0f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,// top right
        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,// bottom right
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,// bottom left
        0.0f,  1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,  // top left
        
        1.0f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,// top right
        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
        1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
        1.0f,  1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, // top left
        
        0.0f,  1.0f, 0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,// top right
        0.0f, 0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,// bottom right
        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,// bottom left
        0.0f,  1.0f, 1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, // top left
        
        1.0f,  1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,// top right
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,// bottom right
        0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,// bottom left
        0.0f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // top left
        
        1.0f,  0.0f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f,// top right
        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,// bottom right
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,// bottom left
        0.0f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, // top left
    });
    
    // ptr to vector of floats
    mes::VectorFloat_uptr verts_uptr(verts_ptr);
   
    // trasnfer verts to vdo object
    mes::VDOFloat tmp_vdo(verts_uptr);
   
    // At offset 0, 3 floats are grouped
    tmp_vdo.addVertexType(mes::VDOFloat::VEC3);
   
    // At offset 3, 2 floats are grouped
    tmp_vdo.addVertexType(mes::VDOFloat::VEC2);
    
    // At offset 5, 3 floats are grouped for normals
    tmp_vdo.addVertexType(mes::VDOFloat::VEC3);
    
    // Move tmp_vdo to vdo member variable
    vdo = std::move(tmp_vdo);
}

void mes::cube::translate(glm::vec3 translation)
{
    mat = glm::translate(mat, translation);
}

mes::VDOFloat& mes::cube::getVerts()
{
    return vdo;
}

std::vector<unsigned int>& mes::cube::getIndices()
{
    return indices;
}

glm::mat4& mes::cube::getTranslation()
{
    return mat;
}
