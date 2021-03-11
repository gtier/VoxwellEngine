//
//  Voxel.hpp
//  MaxwellEngine
//
//  Created by Griffin Dunaif on 11/6/20.
//  Copyright © 2020 Griffin Dunaif. All rights reserved.
//

#ifndef Voxel_hpp
#define Voxel_hpp

#include <stdio.h>
#include "mes.h"
#include <memory>
#include <utility>
#include "cube.hpp"

class Voxel
{
public:
    Voxel()
    {
    }
    
    Voxel(long x, long y, long z)
    {
        cube.translate(glm::vec3(x, y, z));
    }
    
    void translate(long x, long y, long z)
    {
        cube.translate(glm::vec3(x, y, z));
    }
    
    mes::VDOFloat& getVerts()
    {
        return cube.getVerts();
    }
    
    std::vector<unsigned int>& getIndices()
    {
        return cube.getIndices();
    }
    
    glm::mat4& getTranslation()
    {
        return cube.getTranslation();
    }
    
private:
    mes::cube cube;
};

#endif /* Voxel_hpp */
