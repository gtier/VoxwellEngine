//
// Created by Griffin Dunaif on 3/17/21.
//

#include "Tunnels.h"

Tunnels::Tunnels(glm::ivec3 location, glm::ivec3 chunk_dim, glm::ivec2 biome_dim)
: BiomePreset(location, chunk_dim, biome_dim)
{}

siv::PerlinNoise Tunnels::perlin(8149);

bool Tunnels::biome_func(glm::ivec3 v_world_space_location) {
    float x = (float)v_world_space_location.x / (64.0);
    float y = (float)v_world_space_location.y / (64.0);
    float z = (float)v_world_space_location.z / (64.0);

    double val = perlin.accumulatedOctaveNoise3D_0_1(x, y,  z, 20);

    x = (float)v_world_space_location.x - 128.0f;
    y = (float)v_world_space_location.y - 128.0f;
    z = (float)v_world_space_location.z - 128.0f;

    float q = 64.0f - std::sqrt((x * x + y*y));
    if (val > 0.5f && (x*x + y*y + z*z < (128*128))) {
        return true;
    }

    return false;
}

void Tunnels::render(VoxwellEngine& engine) {
    _biome.set_space_mapping(Tunnels::biome_func);
    _biome.populate();
    _biome.render(engine);
}