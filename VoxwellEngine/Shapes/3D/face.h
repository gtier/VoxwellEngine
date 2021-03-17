//
// Created by Griffin Dunaif on 3/16/21.
//

#ifndef FINAL_PROJECT_FACE_H
#define FINAL_PROJECT_FACE_H

#include <vector>
#include <memory>
#include "../../ves.h"
#include "../../VertexDataObject.hpp"

using namespace glm;

class face {
public:
    face();

    face(vec3 location);

    // location is coordinate of bottom-left corner
    void init(vec3 location);

    void translate(vec3 translation);

    std::vector<unsigned int>& get_indices();

    VDOFloat& get_verts();

    mat4& get_model_matrix();

private:
    VDOFloat _vdo;
    std::vector<unsigned int> _indices;
    mat4 _model;
};


#endif //FINAL_PROJECT_FACE_H
