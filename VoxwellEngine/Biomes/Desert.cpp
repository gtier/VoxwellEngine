//
// Created by Griffin Dunaif on 3/17/21.
//

#include "Desert.h"

Desert::Desert(glm::ivec3 location, glm::ivec3 chunk_dim, glm::ivec2 biome_dim)
        : BiomePreset(location, chunk_dim, biome_dim)
{
}

siv::PerlinNoise Desert::perlin(2671);

bool Desert::biome_func(glm::ivec3 v_world_space_location) {
    float x = (float)v_world_space_location.x / (16.0 * 8.0);
    float y = (float)v_world_space_location.y / (64.0);
    float z = (float)v_world_space_location.z / (16.0 * 8.0);

    double val = perlin.accumulatedOctaveNoise2D_0_1(x, z, 3);

    if (y < val) {
        return true;
    }

    return false;
}

void Desert::render(VoxwellEngine &engine) {
    _biome.set_space_mapping(Desert::biome_func);
    _biome.populate();
    _biome.render(engine);
}

