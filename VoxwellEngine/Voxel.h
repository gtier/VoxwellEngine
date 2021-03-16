//
// Created by Griffin Dunaif on 3/10/21.
//

#ifndef FINAL_PROJECT_VOXEL_H
#define FINAL_PROJECT_VOXEL_H

#include "ves.h"
#include "VoxwellEngine.h"
#include "RenderObject.hpp"
#include "VertexDataObject.hpp"
#include "Shapes/3D/cube.hpp"


class Voxel {
public:
    Voxel();

    Voxel(long x, long y, long z);

    void set_visibility(bool is_visible);

    bool is_visible();

    size_t render(VoxwellEngine& engine);
private:
    long _x, _y, _z;
    bool _visible;
};


#endif //FINAL_PROJECT_VOXEL_H
