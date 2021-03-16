//
// Created by Griffin Dunaif on 3/15/21.
//

#ifndef FINAL_PROJECT_CHUNK_H
#define FINAL_PROJECT_CHUNK_H

#include <vector>
#include "Voxel.h"
#include "VoxwellEngine.h"

using namespace std;

class Chunk {
public:
    Chunk(long x, long y, long z, long width, long height, long depth);

    // Populate chunk with voxel data
    void populate();

    void set_chunk_space_mapping(bool func(long x, long y, long z));
    void set_world_space_mapping(bool func(long x, long y, long z));

    void render(VoxwellEngine& engine);

private:
    long voxel_index(long x, long y, long z);

    // Insert voxel into _voxels vector
    void insert_voxel(long x, long y, long z, const Voxel& v);

    Voxel& get_voxel(long x, long y, long z);

    long _width, _height, _depth;
    long _x, _y, _z;
    // one-to-one mapping from voxels to ids
    // Each voxel index corresponds to a render object whose id is stored in _ids
    vector<Voxel> _voxels;
    vector<size_t> _ids;
    long _size;
    bool (*_chunk_space_mapping)(long x, long y, long z);
    bool (*_world_space_mapping)(long x, long y, long z);
};


#endif //FINAL_PROJECT_CHUNK_H
