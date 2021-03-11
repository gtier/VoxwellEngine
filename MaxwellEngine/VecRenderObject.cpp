//
//  VecRenderObject.cpp
//  MaxwellEngine
//
//  Created by Griffin Dunaif on 11/5/20.
//  Copyright © 2020 Griffin Dunaif. All rights reserved.
//

#include "VecRenderObject.hpp"

void mes::VecRenderObject::push_back(RenderObject_uptr &&ro_uptr)
{
    
    std::lock_guard<std::mutex> lg(m);
    renderObjects.push_back(std::move(ro_uptr));
}

size_t mes::VecRenderObject::size()
{
    // TODO think about whether needs mutex lock
    return renderObjects.size();
}

std::unique_ptr<mes::RenderObject>& mes::VecRenderObject::operator[](size_t i)
{
    
    std::lock_guard<std::mutex> lg(m);
    return renderObjects[i];
}
