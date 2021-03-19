//
// Created by Griffin Dunaif on 3/17/21.
//

#ifndef FINAL_PROJECT_BIOMEPRESET_H
#define FINAL_PROJECT_BIOMEPRESET_H

#include "../ves.h"
#include "../VoxwellEngine.h"
#include "../Biome.h"

class BiomePreset {
public:
    BiomePreset(glm::ivec3 location, glm::ivec3 chunk_dim, glm::ivec2 biome_dim);

    virtual void render(VoxwellEngine& engine) = 0;
protected:
    Biome _biome;
};


#endif //FINAL_PROJECT_BIOMEPRESET_H
