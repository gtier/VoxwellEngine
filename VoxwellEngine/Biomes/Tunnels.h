//
// Created by Griffin Dunaif on 3/17/21.
//

#ifndef FINAL_PROJECT_TUNNELS_H
#define FINAL_PROJECT_TUNNELS_H


#include "../ves.h"
#include "../Biome.h"
#include "BiomePreset.h"
#include "../PerlinNoise/PerlinNoise.hpp"
#include <math.h>

using namespace glm;

class Tunnels : BiomePreset {
public:
    Tunnels(glm::ivec3 location, glm::ivec3 chunk_dim, glm::ivec2 biome_dim);

    static bool biome_func(glm::ivec3 v_world_space_location);

    static siv::PerlinNoise perlin;

    void render(VoxwellEngine& engine);
};


#endif //FINAL_PROJECT_TUNNELS_H
