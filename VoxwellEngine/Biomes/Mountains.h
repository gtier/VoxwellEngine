//
// Created by Griffin Dunaif on 3/17/21.
//

#ifndef FINAL_PROJECT_MOUNTAINS_H
#define FINAL_PROJECT_MOUNTAINS_H

#include "../ves.h"
#include "../Biome.h"

using namespace glm;

class Mountains {
public:
    Mountains(ivec3 location,  ivec3 chunk_dim, ivec2 biome_dim);

    static bool world_space_mapping(ivec3 v_world_space);
private:
    ivec3 _location;
    Biome _biome;
};


#endif //FINAL_PROJECT_MOUNTAINS_H
