//
// Created by Griffin Dunaif on 3/16/21.
//

#include "DiscWorld.h"

DiscWorld::DiscWorld(glm::ivec3 center, glm::ivec3 normal, int radius)
: _center(center), _normal(normal), _radius(radius)
{
    _chunks.resize(radius * radius);
}

void DiscWorld::render(VoxwellEngine &engine) {
}
