//
// Created by Griffin Dunaif on 3/17/21.
//

#include "Mountains.h"

Mountains::Mountains(ivec3 location, ivec3 chunk_dim, ivec2 biome_dim)
: _location(location), _biome(location, chunk_dim, biome_dim)
{
}

bool Mountains::world_space_mapping(ivec3 v_world_space) {
    
}
