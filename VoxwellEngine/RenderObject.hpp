//
//  RenderObject.hpp
//  MaxwellEngine
//
//  Created by Griffin Dunaif on 2/5/19.
//  Copyright © 2019 Griffin Dunaif. All rights reserved.
//

#ifndef RenderObject_hpp
#define RenderObject_hpp

#include "ves.h"
#include <glm/glm.hpp>
#include "VertexDataObject.hpp"
#include "VertexAttribute.hpp"
#include "CameraObject.hpp"
#include "TextureObject.hpp"
#include <stdio.h>
#include <iostream>
#include <memory>


class RenderObject
{
private:
    unsigned int VAO, VBO, EBO, EBO_size;
    std::vector<std::unique_ptr<TextureObject> > vec_texture_uptr;
    glm::mat4 modelMatrix;
    
public:
    RenderObject()
    : modelMatrix(1.0f)
    {
        // Get new VAO, VBO, and EBO and save their ids into VAO, VBO, and EBO ints
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
    }
    
    ~RenderObject()
    {
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
        glDeleteVertexArrays(1, &VAO);
    }
    
    template<class T>
    void init(VertexDataObject<T>& vdo, unsigned int indices[], size_t indicesSize);
    void addTexture(const TextureObject& textureObject);
    glm::mat4& getModelMatrix();
    void setModelMatrix(const glm::mat4& model);
    
    // Sets the model to the model times the matrix mat
    void setModelTimesMat(const glm::mat4& mat);
    
    //argument is the shader program id
    void render(const unsigned int shaderProgram_id, const CameraObject& camera);
};

#endif /* RenderObject_hpp */
