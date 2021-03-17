//
// Created by Griffin Dunaif on 3/10/21.
//

#include "Voxel.h"

Voxel::Voxel()
: _location(glm::zero<glm::ivec3>()), _options(0)
{
}

Voxel::Voxel(glm::ivec3 world_space_location) :
_location(world_space_location), _options(0)
{
}

void Voxel::set_visibility(bool is_visible) {
    set_bit_visibility(6, is_visible);
}

void Voxel::set_front_visibility(bool is_visible) {
    set_bit_visibility(0, is_visible);
}

void Voxel::set_back_visibility(bool is_visible) {
    set_bit_visibility(1, is_visible);
}

void Voxel::set_left_visibility(bool is_visible) {
    set_bit_visibility(2, is_visible);
}

void Voxel::set_right_visibility(bool is_visible) {
    set_bit_visibility(3, is_visible);
}

void Voxel::set_up_visibility(bool is_visible) {
    set_bit_visibility(4, is_visible);
}

void Voxel::set_down_visibility(bool is_visible) {
    set_bit_visibility(5, is_visible);
}

void Voxel::set_bit_visibility(int bit_index, bool is_visible) {
    if (is_visible) {
        set_bit_true(bit_index);
    } else {
        set_bit_false(bit_index);
    }
}

void Voxel::set_bit_true(int bit_index) {
    if (bit_index > 7) {
        return;
    }

    char mask = 1;
    mask = mask << bit_index;

    _options = _options | mask;
}

void Voxel::set_bit_false(int bit_index) {
    if (bit_index > 7) {
        return;
    }

    char mask = 1;
    mask = mask << bit_index;
    mask = ~mask;

    _options = _options & mask;
}

bool Voxel::is_bit_true(int bit_index) {
    if (bit_index > 7) {
        return false;
    }

    char mask = 1;
    mask = mask << bit_index;

    return (_options & mask) > 0;
}

bool Voxel::is_visible() {
    return is_bit_true(6);
}

bool Voxel::is_front_visible() {
    return is_bit_true(0);
}

bool Voxel::is_back_visible() {
    return is_bit_true(1);
}

bool Voxel::is_left_visible() {
    return is_bit_true(2);
}

bool Voxel::is_right_visible() {
    return is_bit_true(3);
}

bool Voxel::is_up_visible() {
    return is_bit_true(4);
}

bool Voxel::is_down_visible() {
    return is_bit_true(5);
}

optional<size_t> Voxel::render(VoxwellEngine& engine) {
    if (is_visible()) {
        if (is_front_visible()) {
            face f(_location);
            size_t id = engine.create_render_object(f.get_verts(), f.get_indices());
            RenderObject &obj = engine.get_render_object(id);
            obj.setModelMatrix(f.get_model_matrix());

            return id;
        }

        return nullopt;
    }

    return nullopt;
}
