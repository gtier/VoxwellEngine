//
// Created by Griffin Dunaif on 3/17/21.
//

#include "SpaceMapping.h"

SpaceMapping::SpaceMapping()
: _basis_center(zero<ivec3>()), _mapping(nullptr)
{
}

SpaceMapping::SpaceMapping(ivec3 basis_center, bool (*mapping)(ivec3))
: _basis_center(basis_center), _mapping(mapping)
{
}

void SpaceMapping::set_basis_center(ivec3 basis_center) {
    _basis_center = basis_center;
}

void SpaceMapping::set_mapping(bool (*mapping)(ivec3)) {
    _mapping = mapping;
}