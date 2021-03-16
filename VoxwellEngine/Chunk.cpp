//
// Created by Griffin Dunaif on 3/15/21.
//

#include "Chunk.h"

Chunk::Chunk(long x, long y, long z, long width, long height, long depth)
: _width(width), _height(height), _depth(depth), _world_space_mapping(nullptr),
_x(x), _y(y), _z(z)
{
    _size = width * height * depth;
    _voxels.resize(_size);
    _ids.resize(_size);
}

void Chunk::populate() {
    if (!_world_space_mapping) {
        return;
    }

    for (long x = 0; x < _width; ++x) {
        for (long y = 0; y < _height; ++y) {
            for (long z = 0; z < _depth; ++z) {
                // Basis of chunk
                Voxel v(_x + x, _y + y, _z + z);

                if (_world_space_mapping(_x + x, _y + y , _z + z)) {
                    v.set_visibility(true);
                } else {
                    v.set_visibility(false);
                }

                insert_voxel(x, y, z, v);
            }
        }
    }
}

long Chunk::voxel_index(long x, long y, long z) {
    return x + y * _width + z * _width * _height;
}

void Chunk::insert_voxel(long x, long y, long z, const Voxel &v) {
    _voxels[voxel_index(x, y, z)] = v;
}

Voxel& Chunk::get_voxel(long x, long y, long z) {
    return _voxels[voxel_index(x, y, z)];
}

void Chunk::render(VoxwellEngine &engine) {
    for (long x = 0; x < _width; ++x) {
        for (long y = 0; y < _height; ++y) {
            for (long z = 0; z < _depth; ++z) {
                Voxel& v = get_voxel(x, y, z);

                if (x == 0 || y == 0 || z == 0
                || x == _width - 1 || y == _height - 1 || z == _depth - 1
                || !get_voxel(x + 1, y, z).is_visible() || !get_voxel(x - 1, y, z).is_visible()
                || !get_voxel(x, y +  1, z).is_visible() || !get_voxel(x, y - 1, z).is_visible()
                || !get_voxel(x, y, z + 1).is_visible() || !get_voxel(x, y, z - 1).is_visible()) {
                    size_t id = v.render(engine);
                    _ids[voxel_index(x, y, z)] = id;
                }
            }
        }
    }
}

void Chunk::set_chunk_space_mapping(bool (*func)(long, long, long)) {
    _chunk_space_mapping = func;
}

void Chunk::set_world_space_mapping(bool (*func)(long, long, long)) {
    _world_space_mapping = func;
}