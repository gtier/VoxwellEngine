//
// Created by Griffin Dunaif on 3/16/21.
//

#ifndef FINAL_PROJECT_DISCWORLD_H
#define FINAL_PROJECT_DISCWORLD_H

#include "ves.h"
#include "VoxwellEngine.h"
#include "Chunk.h"
#include <vector>
#include <memory>

using namespace std;

// Creates a planet in the shape of a disc
class DiscWorld {
public:
    DiscWorld(glm::ivec3 center, glm::ivec3 normal, int radius);

    void render(VoxwellEngine& engine);
private:
    glm::ivec3 _center, _normal;
    int _radius;
    vector<unique_ptr<Chunk>> _chunks;
};


#endif //FINAL_PROJECT_DISCWORLD_H
