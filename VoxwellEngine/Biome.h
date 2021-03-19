//
// Created by Griffin Dunaif on 3/17/21.
//

#ifndef FINAL_PROJECT_BIOME_H
#define FINAL_PROJECT_BIOME_H

#include "ves.h"
#include "Chunk.h"
#include "VoxwellEngine.h"
#include "SpaceMapping.h"

using namespace std;

class Biome {
public:
    Biome(glm::ivec3 location, glm::ivec3 chunk_dim, glm::ivec2 biome_dim);

    void populate();

    int chunk_index(int x, int y);

    // converts x, y world units in chunk sizes to world space
    glm::vec3 world_units_to_world_space(glm::ivec2 world_units);

    void set_space_mapping(bool (*_mapping)(ivec3 v_world_location));

    void render(VoxwellEngine& engine);
private:
    glm::ivec3 _location;
    glm::ivec3 _chunk_dim;
    glm::ivec2 _biome_dim;
    vector<unique_ptr<Chunk>> _chunks;
    SpaceMapping _mapping;
};


#endif //FINAL_PROJECT_BIOME_H
