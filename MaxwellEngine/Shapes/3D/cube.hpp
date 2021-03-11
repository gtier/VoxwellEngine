//
//  cube.hpp
//  MaxwellEngine
//
//  Created by Griffin Dunaif on 11/5/20.
//  Copyright © 2020 Griffin Dunaif. All rights reserved.
//

#ifndef cube_hpp
#define cube_hpp

#include <stdio.h>
#include "mes.h"
#include <memory>
#include <utility>

namespace mes {
    class cube{
    private:
        VDOFloat vdo;
        // verts_ptr gets put into a unique_ptr and transfers ownership to vdo
        std::vector<unsigned int> indices;
        glm::mat4 mat;
        
    public:
        cube();
        
        void translate(glm::vec3 translatation);
        
        VDOFloat& getVerts();
        
        std::vector<unsigned int>& getIndices();
        
        glm::mat4& getTranslation();
        
    };
}

#endif /* cube_hpp */
