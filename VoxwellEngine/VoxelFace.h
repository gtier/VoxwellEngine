//
// Created by Griffin Dunaif on 3/16/21.
//

#ifndef FINAL_PROJECT_VOXELFACE_H
#define FINAL_PROJECT_VOXELFACE_H

#include "ves.h"
#include <vector>
#include <memory>

using namespace std;

enum Face {
    FRONT,
    BACK,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class VoxelFace {
public:
    typedef vector<unsigned int> _indices_t;
    typedef vector<float> _verts_t;

    // 8 floats for every vertex
    static int stride;

    // 6 indices
    static int indices_size;

    // 8 floats per vertex
    static int verts_size;

    static _indices_t indices;

    static _verts_t front_verts;

    static _verts_t back_verts;

    static _verts_t left_verts;

    static _verts_t right_verts;

    static _verts_t up_verts;

    static _verts_t down_verts;

    // Index used to compute indices offset
    static void compute_verts(glm::vec3 location, Face face, vector<float>& output);

    static void compute_indices(int index, vector<unsigned int>& output);
};


#endif //FINAL_PROJECT_VOXELFACE_H
