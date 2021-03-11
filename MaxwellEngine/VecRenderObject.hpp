//
//  VecRenderObject.hpp
//  MaxwellEngine
//
//  Created by Griffin Dunaif on 11/5/20.
//  Copyright © 2020 Griffin Dunaif. All rights reserved.
//

#ifndef VecRenderObject_hpp
#define VecRenderObject_hpp

#include <stdio.h>
#include <mutex>

#include "mes.h"
#include "RenderObject.hpp"

class mes::VecRenderObject
{
private:
    typedef std::unique_ptr<mes::RenderObject> RenderObject_uptr;
    std::vector<std::unique_ptr<mes::RenderObject>> renderObjects;
    std::mutex m;
    
public:
    VecRenderObject()
    {
    }
    
    void push_back(RenderObject_uptr&& ro_uptr);
    
    size_t size();
    
    // Overrides [] operator
    std::unique_ptr<mes::RenderObject>& operator[](size_t i);
};

#endif /* VecRenderObject_hpp */
