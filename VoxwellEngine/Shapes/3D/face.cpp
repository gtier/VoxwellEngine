//
// Created by Griffin Dunaif on 3/16/21.
//

#include "face.h"

face::face()
: _indices ({
        0, 1, 3, // first triangle
        1, 2, 3,  // second triangle
    })
{
    init(zero<vec3>());
}

face::face(vec3 location)
: _indices({
        0, 1, 3, // first triangle
        1, 2, 3,  // second triangle
    })
{
    init(location);
}

void face::translate(vec3 translation) {
    _model = glm::translate(_model, translation);
}

std::vector<unsigned int>& face::get_indices() {
    return _indices;
}

VDOFloat & face::get_verts() {
    return _vdo;
}

mat4 & face::get_model_matrix() {
    return _model;
}

void face::init(vec3 location) {
    _model = identity<mat4>();

    std::vector<float>* verts_ptr = new std::vector<float>({
           1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, // top right
           1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom right
           0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom left
           0.0f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // top left
    });

    std::unique_ptr<std::vector<float>> tmp_uptr(verts_ptr);

    VDOFloat tmp_vdo(tmp_uptr);

    // vec3 location
    tmp_vdo.addVertexType(VDOFloat::VEC3);

    // vec2 uv
    tmp_vdo.addVertexType(VDOFloat::VEC2);

    // vec3 normal
    tmp_vdo.addVertexType(VDOFloat::VEC3);

    _vdo = std::move(tmp_vdo);

    translate(location);
}