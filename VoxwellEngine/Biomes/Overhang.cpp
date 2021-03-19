//
// Created by Griffin Dunaif on 3/17/21.
//

#include "Overhang.h"

Overhang::Overhang(glm::ivec3 location, glm::ivec3 chunk_dim, glm::ivec2 biome_dim)
: BiomePreset(location, chunk_dim, biome_dim)
{
}

siv::PerlinNoise Overhang::perlin(4242);

bool Overhang::biome_func(glm::ivec3 v_world_space_location) {
    float x = (float)v_world_space_location.x / (16.0 * 32.0);
    float y = (float)v_world_space_location.y / (32.0);
    float z = (float)v_world_space_location.z / (16.0 * 32.0);

    double val = perlin.accumulatedOctaveNoise3D_0_1(x, y,  z, 1);

    if (val > 0.5) {
        return true;
    }

    return false;
}

void Overhang::render(VoxwellEngine& engine) {
    _biome.set_space_mapping(Overhang::biome_func);
    _biome.populate();
    _biome.render(engine);
}