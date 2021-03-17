//
// Created by Griffin Dunaif on 3/10/21.
//

#ifndef FINAL_PROJECT_VOXEL_H
#define FINAL_PROJECT_VOXEL_H

#include "ves.h"
#include "VoxwellEngine.h"
#include "RenderObject.hpp"
#include "VertexDataObject.hpp"
#include "Shapes/3D/cube.hpp"
#include "Shapes/3D/face.h"
#include <optional>
#include <cstddef>
#include <iostream>

using namespace std;

class Voxel {
public:
    Voxel();

    Voxel(glm::ivec3 world_space_location);

    void set_visibility(bool is_visible);

    void set_front_visibility(bool is_visible);

    void set_back_visibility(bool is_visible);

    void set_left_visibility(bool is_visible);

    void set_right_visibility(bool is_visible);

    void set_up_visibility(bool is_visible);

    void set_down_visibility(bool is_visible);

    void set_bit_true(int bit_index);

    void set_bit_false(int bit_index);

    void set_bit_visibility(int bit_index, bool is_visible);

    bool is_bit_true(int bit_index);

    bool is_visible();

    bool is_front_visible();

    bool is_back_visible();

    bool is_right_visible();

    bool is_left_visible();

    bool is_up_visible();

    bool is_down_visible();

    optional<size_t> render(VoxwellEngine& engine);
private:
    // coordinate of bottom-left-front corner in world space
    glm::ivec3 _location;

    // defines a byte that controls the options of a voxel
    // 0b00000000
    // The first 6 bytes (from right to left) correspond to which faces should be visible
    // (each number is i'th bit) 0 -> front, 1 -> back, 2 -> left, 3 -> right
    // 4 -> up, 5 -> down
    char _options;
};


#endif //FINAL_PROJECT_VOXEL_H
