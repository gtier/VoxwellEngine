//
// Created by Griffin Dunaif on 3/16/21.
//

#include "VoxelFace.h"

int VoxelFace::stride = 8;

int VoxelFace::indices_size = 6;

int VoxelFace::verts_size = 8 * 4;

VoxelFace::_indices_t VoxelFace::indices = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
};

VoxelFace::_verts_t VoxelFace::front_verts = {
        1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, // top right
        1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom right
        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom left
        0.0f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // top left
};

VoxelFace::_verts_t VoxelFace::back_verts = {
        0.0f,  1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, // top right
        0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, // bottom right
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, // bottom left
        1.0f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, // top left
};

VoxelFace::_verts_t VoxelFace::left_verts = {
        0.0f,  1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, // top right
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, // bottom right
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // bottom left
        0.0f,  1.0f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, // top left
};

VoxelFace::_verts_t VoxelFace::right_verts = {
        1.0f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // top right
        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
        1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
        1.0f,  1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, // top left
};

VoxelFace::_verts_t VoxelFace::up_verts = {
        1.0f,  1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, // top right
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right
        0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
        0.0f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // top left
};

VoxelFace::_verts_t VoxelFace::down_verts = {
        0.0f,  0.0f, 0.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, // top right
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, // bottom right
        1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, // bottom left
        1.0f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, // top left
};

void VoxelFace::compute_verts(glm::vec3 location, Face face, vector<float> &output) {
    // 3 floats per vertex and 4 vertices
    vector<float>* v;
    switch (face) {
        case FRONT:
            v = &VoxelFace::front_verts;
            break;
        case BACK:
            v = &VoxelFace::back_verts;
            break;
        case LEFT:
            v = &VoxelFace::left_verts;
            break;
        case RIGHT:
            v = &VoxelFace::right_verts;
            break;
        case UP:
            v = &VoxelFace::up_verts;
            break;
        case DOWN:
            v = &VoxelFace::down_verts;
            break;
    }

    for (int i = 0; i < VoxelFace::verts_size; i += VoxelFace::stride) {
        glm::vec3 vertex_pos(v->at(i), v->at(i + 1), v->at(i + 2));
        glm::vec3 new_pos = location + vertex_pos;
        output[i] = new_pos.x;
        output[i+1]= new_pos.y;
        output[i+2] = new_pos.z;
        for (int x = i + 3; x < i + 8; ++x) {
            output[x] = v->at(x);
        }
    }
};

void VoxelFace::compute_indices(int index, vector<unsigned int> &output) {
    for (int i = 0; i < VoxelFace::indices_size; ++i) {
        output[i] = VoxelFace::indices[i] + 4 * index;
    }
}
