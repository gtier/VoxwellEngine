//
// Created by Griffin Dunaif on 3/15/21.
//

#ifndef FINAL_PROJECT_CHUNK_H
#define FINAL_PROJECT_CHUNK_H

#include "ves.h"
#include <vector>
#include "Voxel.h"
#include "VoxwellEngine.h"
#include "VoxelFace.h"
#include "SpaceMapping.h"

using namespace std;

class Chunk {
public:
    Chunk(glm::ivec3 location, int width, int height, int depth);

    // Populate chunk with voxel data
    void populate();

    void set_space_mapping(const SpaceMapping& mapping);

    void render(VoxwellEngine& engine);

    void add_face(glm::ivec3 location, Face face, vector<float>& output_verts, vector<unsigned int>& output_indices, int& output_index);

private:
    // Gets index in _voxels array of a voxel at a certain (x, y, z) in chunk space
    int voxel_index(glm::ivec3 chunk_space_location);

    // Gets index in _voxels array given x, y, z components
    int voxel_index(int x, int y, int z);

    // Insert voxel into _voxels vector
    void insert_voxel(glm::ivec3 chunk_space_location, const Voxel& v);

    // Gets a voxel that is at location v = (x, y, z) in chunk space
    Voxel& get_voxel(glm::ivec3 chunk_space_location);

    // Gets a voxel given vector components
    Voxel& get_voxel(int x, int y, int z);

    // gets location of a voxel at x, y, z in chunk space, which has basis at bottom-left-front corner
    glm::ivec3 voxel_chunk_space_location(int x, int y, int z);

    // gets location of a voxel at x, y, z in chunk space and returns its location in world space
    glm::ivec3 voxel_world_space_location(int x, int y, int z);

    // Converts chunk space to world space
    glm::ivec3 chunk_to_world_space_transform(glm::ivec3 chunk_space_location);

    // Converts world space to chunk space
    glm::ivec3 world_space_to_chunk_space_transform(glm::ivec3 world_space_location);

    int _width, _height, _depth;
    // location is position of bottom-left-front corner of chunk
    glm::ivec3 _location;
    SpaceMapping _mapping;

    // one-to-one mapping from voxels to ids
    // Each voxel index corresponds to a render object whose id is stored in _ids
    vector<Voxel> _voxels;
    vector<size_t> _ids;
    int _size;

    // mesh
    vector<unsigned int> _indices;
    VDOFloat _vdo;
    // id of mesh as stored as a render object
    size_t _id;
    glm::mat4 _model;
};


#endif //FINAL_PROJECT_CHUNK_H
