//
//  MaxwellEngine.hpp
//  MaxwellEngine
//
//  Created by Griffin Dunaif on 2/5/19.
//  Copyright © 2019 Griffin Dunaif. All rights reserved.
//

#ifndef MaxwellEngine_hpp
#define MaxwellEngine_hpp

#include <stdio.h>
#include <vector>
#include <map>
#include <memory>
#include <utility>
#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "mes.h"
#include "RenderObject.hpp"
#include "CameraObject.hpp"
#include "ShaderProgram.hpp"
#include "VecRenderObject.hpp"
#include "ThreadsafeQueue.hpp"

class mes::MaxwellEngine
{
public:
    typedef std::vector<std::unique_ptr<mes::ShaderProgram>> VecShaderProgram;
    typedef void (*renderIntercept_t)(MaxwellEngine& engine);
    typedef void (*handleInput_t)(GLFWwindow* window);
    typedef unsigned long obj_id;
    
    struct RenderObjectData {
        mes::VDOFloat verts;
        std::vector<unsigned int> indices;
        
        // TODO consider passing by move or ref
        glm::mat4 translation;
        
        RenderObjectData()
        {
        }
        
        RenderObjectData(RenderObjectData&& other)
        {
            verts = std::move(other.verts);
            indices = std::move(other.indices);
            translation = std::move(other.translation);
        }
        
        RenderObjectData& operator=(RenderObjectData&& other)
        {
            verts = std::move(other.verts);
            indices = std::move(other.indices);
            translation = std::move(other.translation);
            
            return *this;
        }
    };
    
    typedef struct RenderObjectData RenderObjectData;
    
private:
    GLFWwindow* engineWindow;
    unsigned int engineVertexShader, engineFragmentShader, engineShaderProgram;
    VecRenderObject vecRenderObject;
    ThreadsafeQueue<RenderObjectData> queueRenderObject;
    VecShaderProgram vecShaderProgram;
    CameraObject mainCamera;
    std::vector<handleInput_t> vecHandleInput;
    bool toHandleInput = false;
    bool handleKeyConfig = false, handleCursorConfig = false, cursorHandlerMounted = false, keyHandlerMounted = false,
    cameraIsInputHandler = false;
    float deltaFrameTime, lastFrameTime, currFrameTime;
    std::queue<obj_id> emptyQueue;
    
public:
    MaxwellEngine(mes::ShaderFile& vertShader, mes::ShaderFile& fragmentShader)
    : mainCamera(800, 600), deltaFrameTime(0.0f), lastFrameTime(0.0f), currFrameTime(0.0f)
    {
        init(800, 600, vertShader, fragmentShader);
    }
    
    MaxwellEngine(int width, int height, mes::ShaderFile& vertShader, mes::ShaderFile& fragmentShader)
    : mainCamera(width, height), deltaFrameTime(0.0f), lastFrameTime(0.0f), currFrameTime(0.0f)
    {
        init(width, height, vertShader, fragmentShader);
    }
    
    static void frame_resize(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }
    
    template <class T>
    obj_id createRenderObject(mes::VertexDataObject<T>& verts, std::vector<unsigned int>& indices);
    
    // TODO maybe template
    void queueRenderObjectCreation(mes::VertexDataObject<float>& verts, std::vector<unsigned int>& indices,
                                   glm::mat4& translation);
    
    void deleteRenderObject(const obj_id id);
    
    obj_id createShaderProgram(mes::ShaderFile& vertShader, mes::ShaderFile& fragmentShader);
    
    mes::RenderObject& getRenderObject(obj_id id)
    {
        return *vecRenderObject[id];
    }
    
    mes::VecRenderObject& getVecRenderObject() {
        return vecRenderObject;
    }
    
    mes::CameraObject& getMainCamera()
    {
        return mainCamera;
    }
    
    void startRenderLoop();
    
    void startRenderLoop(handleInput_t);
    
    void startRenderLoop(renderIntercept_t);
    
    void startRenderLoop(handleInput_t, renderIntercept_t);
    
    void stopRenderLoop();
    
    void addInputHandler(const handleInput_t& handler);
    
    static void cursorHandler(GLFWwindow* window, double x, double y);
    
    //TODO add enum options for different camera modes or objects that control cursor.
    void mountStaticCamera();
    
    void enableCursorHanler();
    
    void enableKeyHandler();
    
private:
    void init(int width, int height, mes::ShaderFile& vertShader, mes::ShaderFile& fragmentShader);
    
    void renderLoop(handleInput_t handleInput, renderIntercept_t renderIntercept);
    
    void renderFrame();
};


#endif /* MaxwellEngine_hpp */
