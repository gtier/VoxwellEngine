//
//  VoxwellEngine.cpp
//  GriffRoboVoxelTech
//
//  Created by student on 4/23/19.
//  Copyright © 2019 student. All rights reserved.
//

#include "VoxwellEngine.hpp"

void ves::VoxwellEngine::init()
{
    // Sets initial camera position
    engine.getMainCamera().setViewMatrix(glm::translate(engine.getMainCamera().getViewMatrix(), glm::vec3(0.0f, 0.0f, -5.0f)));
    
    engine.getMainCamera().setSpeed(10.0f);
    
    engine.getMainCamera().setSensitivity(0.25f);
    
    // Enables user to use cursor
    engine.enableCursorHanler();
    
    // Mounts mainCamera to static camera
    engine.mountStaticCamera();
}


void ves::VoxwellEngine::start()
{
    //Set up VoxwellEngine to start on another thread
    //Make a command queue
    
    // Gets the vector containing all the render objects in MaxwellEngine
    // VecRenderObject is thread-safe
    mes::VecRenderObject& EngineVecRenderObject = engine.getVecRenderObject();
    
    std::thread worldBuilderThread = std::thread([this, &EngineVecRenderObject]{
        for (int z = 0; z < 10; z++) {
            for (int y = 0; y < 10; y++) {
                for (int x = 0; x < 10; x++) {
                    Voxel voxel(x, y, z);
                    
                    // rendering all these cubes is hugely inefficient
                    // should abstract voxels and merge them into a mesh
                    engine.queueRenderObjectCreation(voxel.getVerts(), voxel.getIndices(), voxel.getTranslation());
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                }
            }
        }
    });
    
    engine.startRenderLoop();
}
