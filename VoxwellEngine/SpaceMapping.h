//
// Created by Griffin Dunaif on 3/17/21.
//

#ifndef FINAL_PROJECT_SPACEMAPPING_H
#define FINAL_PROJECT_SPACEMAPPING_H

#include "ves.h"

using namespace glm;

class SpaceMapping {
public:
    // default space mapping. maps in basis_center of (0, 0, 0) and accepts all voxels
    SpaceMapping();

    SpaceMapping(ivec3 basis_center, bool (*mapping)(ivec3 v_world_location));

    void set_basis_center(ivec3 basis_center);

    void set_mapping(bool (*mapping)(ivec3 v_world_location));

    bool operator () (ivec3 v_world_location) {
        if (!_mapping) {
            return true;
        }

        ivec3 v_space = v_world_location - _basis_center;
        return _mapping(v_space);
    }

private:
    ivec3 _basis_center;
    bool (*_mapping)(ivec3 v_world_location);
};


#endif //FINAL_PROJECT_SPACEMAPPING_H
