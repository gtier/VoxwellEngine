//
// Created by Griffin Dunaif on 3/17/21.
//

#include "Mountains.h"

Mountains::Mountains(glm::ivec3 location, glm::ivec3 chunk_dim, glm::ivec2 biome_dim)
: BiomePreset(location, chunk_dim, biome_dim)
{
}

siv::PerlinNoise Mountains::perlin(2671);

bool Mountains::biome_func(glm::ivec3 v_world_space_location) {
    float x = (float)v_world_space_location.x / (16.0 * 4.0);
    float y = (float)v_world_space_location.y / (128.0);
    float z = (float)v_world_space_location.z / (16.0 * 4.0);

    double val = perlin.accumulatedOctaveNoise2D_0_1(x, z, 4);

    if (y < val || y < 0.2) {
        return true;
    }

    return false;
}

void Mountains::render(VoxwellEngine &engine) {
    _biome.set_space_mapping(Mountains::biome_func);
    _biome.populate();
    _biome.render(engine);
}

