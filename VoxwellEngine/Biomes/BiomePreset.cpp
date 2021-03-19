//
// Created by Griffin Dunaif on 3/17/21.
//

#include "BiomePreset.h"

BiomePreset::BiomePreset(glm::ivec3 location, glm::ivec3 chunk_dim, glm::ivec2 biome_dim)
: _biome(location, chunk_dim, biome_dim)
{
}