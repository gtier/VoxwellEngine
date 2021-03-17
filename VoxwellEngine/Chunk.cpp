//
// Created by Griffin Dunaif on 3/15/21.
//

#include "Chunk.h"

Chunk::Chunk(glm::ivec3 location, int width, int height, int depth)
: _width(width), _height(height), _depth(depth), _world_space_mapping(nullptr),
_location(location), _model(glm::identity<glm::mat4>())
{
    _size = width * height * depth;
    _voxels.resize(_size);
    _ids.resize(_size);
    _model = glm::translate(_model, glm::vec3((float)location.x, (float)location.y, (float)location.z));
}

void Chunk::populate() {
    if (!_world_space_mapping) {
        return;
    }

    for (int x = 0; x < _width; ++x) {
        for (int y = 0; y < _height; ++y) {
            for (int z = 0; z < _depth; ++z) {
                // Basis of chunk
                glm::ivec3 v_chunk_space_location = voxel_chunk_space_location(x, y, z);
                glm::ivec3 v_world_space_location = chunk_to_world_space_transform(v_chunk_space_location);
                Voxel v(v_world_space_location);

                if (_world_space_mapping(v_world_space_location)) {
                    v.set_visibility(true);
                } else {
                    v.set_visibility(false);
                }

                insert_voxel(v_chunk_space_location, v);
            }
        }
    }
}

int Chunk::voxel_index(glm::ivec3 chunk_space_location) {
    int x = chunk_space_location.x;
    int y = chunk_space_location.y;
    int z = chunk_space_location.z;

    return voxel_index(x, y, z);
}

int Chunk::voxel_index(int x, int y, int z) {
    return x + y * _width + z * _width * _height;
}

glm::ivec3 Chunk::voxel_chunk_space_location(int x, int y, int z) {
    return glm::ivec3(x, y, z);
}

glm::ivec3 Chunk::voxel_world_space_location(int x, int y, int z) {
    return _location + glm::ivec3(x, y, z);
}

glm::ivec3 Chunk::world_space_to_chunk_space_transform(glm::ivec3 world_space_location) {
    return world_space_location - _location;
}

glm::ivec3 Chunk::chunk_to_world_space_transform(glm::ivec3 chunk_space_location) {
    return _location + chunk_space_location;
}

void Chunk::insert_voxel(glm::ivec3 chunk_space_location, const Voxel &v) {
    _voxels[voxel_index(chunk_space_location)] = v;
}

Voxel& Chunk::get_voxel(glm::ivec3 chunk_space_location) {
    return _voxels[voxel_index(chunk_space_location)];
}

Voxel& Chunk::get_voxel(int x, int y, int z) {
    return _voxels[voxel_index(x, y, z)];
}

void Chunk::render(VoxwellEngine &engine) {

    // Visibility pass
    for (int x = 0; x < _width; ++x) {
        for (int y = 0; y < _height; ++y) {
            for (int z = 0; z < _depth; ++z) {
                Voxel& v = get_voxel(x, y, z);

                // Check if voxel is visible
                if (!v.is_visible()) continue;

                // front face
                if (z == _depth - 1 || !get_voxel(x, y, z + 1).is_visible()) {
                    v.set_front_visibility(true);
                } else {
                    v.set_front_visibility(false);
                }

                // back face
                if (z == 0 || !get_voxel(x, y, z - 1).is_visible()) {
                    v.set_back_visibility(true);
                } else {
                    v.set_back_visibility(false);
                }

                // left face
                if (x == 0 || !get_voxel(x - 1, y, z).is_visible()) {
                    v.set_left_visibility(true);
                } else {
                    v.set_left_visibility(false);
                }

                // right face
                if (x == _width - 1 || !get_voxel(x + 1, y, z).is_visible()) {
                    v.set_right_visibility(true);
                } else {
                    v.set_right_visibility(false);
                }

                // up face
                if (y == _height - 1 || !get_voxel(x, y + 1, z).is_visible()) {
                    v.set_up_visibility(true);
                } else {
                    v.set_up_visibility(false);
                }

                // down face
                if (y == 0 || !get_voxel(x, y - 1, z).is_visible()) {
                    v.set_down_visibility(true);
                } else {
                    v.set_down_visibility(false);
                }
            }
        }
    }

    // Merge mesh pass
    int index = 0;
    // new vector on heap. Ends up being handled by unique pointer and passed to a VDO
    auto* mesh_verts = new vector<float>();
    for (int x = 0; x < _width; ++x) {
        for (int y = 0; y < _height; ++y) {
            for (int z = 0; z < _depth; ++z) {
                Voxel& v = get_voxel(x, y, z);
                glm::ivec3 v_chunk_space = voxel_chunk_space_location(x, y, z);

                // front face
                if (v.is_front_visible()) {
                    add_face(v_chunk_space, Face::FRONT, *mesh_verts, _indices, index);
                }

                // back face
                if (v.is_back_visible()) {
                    add_face(v_chunk_space, Face::BACK, *mesh_verts, _indices, index);
                }

                // left face
                if (v.is_left_visible()) {
                    add_face(v_chunk_space, Face::LEFT, *mesh_verts, _indices, index);
                }

                // right face
                if (v.is_right_visible()) {
                    add_face(v_chunk_space, Face::RIGHT, *mesh_verts, _indices, index);
                }

                // up face
                if (v.is_up_visible()) {
                    add_face(v_chunk_space, Face::UP, *mesh_verts, _indices, index);
                }

                // down face
                if (v.is_down_visible()) {
                    add_face(v_chunk_space, Face::DOWN, *mesh_verts, _indices, index);
                }

            }
        }
    }

    unique_ptr<vector<float> > tmp_uptr = unique_ptr<vector<float> >(mesh_verts);
    VDOFloat tmp_vdo(tmp_uptr);
    tmp_vdo.addVertexType(VDOFloat::VEC3);
    tmp_vdo.addVertexType(VDOFloat::VEC2);
    tmp_vdo.addVertexType(VDOFloat::VEC3);
    _vdo = move(tmp_vdo);

    optional<size_t> id = engine.create_render_object(_vdo, _indices);

    if (id.has_value()) {
        _id = id.value();
        RenderObject& obj = engine.get_render_object(_id);
        obj.setModelMatrix(_model);
    }
}

void Chunk::add_face(glm::ivec3 location, Face face,
                     vector<float> &output_verts, vector<unsigned int> &output_indices, int& output_index) {
    vector<float> verts(VoxelFace::verts_size);
    VoxelFace::compute_verts(location, face, verts);

    vector<unsigned int> indices(VoxelFace::indices_size);
    VoxelFace::compute_indices(output_index, indices);

    // TODO make more efficient
    for (auto i: verts) {
        output_verts.push_back(i);
    }

    for (auto i: indices) {
        output_indices.push_back(i);
    }

    // update index whenever face added
    output_index++;
}

void Chunk::set_chunk_space_mapping(bool (*func)(glm::ivec3)) {
    _chunk_space_mapping = func;
}

void Chunk::set_world_space_mapping(bool (*func)(glm::ivec3)) {
    _world_space_mapping = func;
}