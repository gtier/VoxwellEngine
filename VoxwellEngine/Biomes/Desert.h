//
// Created by Griffin Dunaif on 3/17/21.
//

#ifndef FINAL_PROJECT_DESERT_H
#define FINAL_PROJECT_DESERT_H

#include "../ves.h"
#include "../Biome.h"
#include "BiomePreset.h"
#include "../PerlinNoise/PerlinNoise.hpp"

using namespace glm;

class Desert : BiomePreset {
public:
    Desert(glm::ivec3 location, glm::ivec3 chunk_dim, glm::ivec2 biome_dim);

    static bool biome_func(glm::ivec3 v_world_space_location);

    static siv::PerlinNoise perlin;

    void render(VoxwellEngine& engine);
};


#endif //FINAL_PROJECT_DESERT_H
