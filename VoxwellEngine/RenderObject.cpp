//
//  RenderObject.cpp
//  MaxwellEngine
//
//  Created by Griffin Dunaif on 2/5/19.
//  Copyright © 2019 Griffin Dunaif. All rights reserved.
//

#include <glm/gtc/type_ptr.hpp>
#include "RenderObject.hpp"
#include "CameraObject.hpp"

template <class T>
void RenderObject::init(VertexDataObject<T>& vdo, unsigned int indices[], size_t indicesSize)
{
    // Bind vertex array to private member VAO int
    glBindVertexArray(VAO);
    
    // Bind array buffer to private member VBO int
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    // Copy data into the array buffer
    glBufferData(GL_ARRAY_BUFFER, vdo.getSize(), vdo.getVertexArray(), GL_STATIC_DRAW);
    
    // Bind element array to EBO int
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    
    // Copy indices into EBO buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);
    
    // Create vertex attributes
    std::vector<VertexAttribute> vertexAttributeList;
    // Passed by reference and loads vertex attributes into vertexAttributeList
    vdo.createVertexAttributeList(vertexAttributeList);
    for (int i = 0; i < vertexAttributeList.size(); ++i)
    {
        // Create vertex atrribute
        // Location is used to load data into the shader (e.g. layout (location = 0))
        glVertexAttribPointer(vertexAttributeList.at(i).location, vertexAttributeList.at(i).dimension, vertexAttributeList.at(i).type, vertexAttributeList.at(i).normalized, vertexAttributeList.at(i).stride, vertexAttributeList.at(i).offset);
        // Enable attribute at current location
        glEnableVertexAttribArray(vertexAttributeList.at(i).location);
    }
    
    // unbind VAO
    glBindVertexArray(0);
    
    EBO_size = static_cast<unsigned int>(indicesSize / sizeof(unsigned int));
}

//init templates
template void RenderObject::init<float>(VertexDataObject<float>&, unsigned int indices[], size_t);

template void RenderObject::init<int>(VertexDataObject<int>&, unsigned int indices[], size_t);

template void RenderObject::init<double>(VertexDataObject<double>&, unsigned int indices[], size_t);

void RenderObject::addTexture(const TextureObject& textureObject)
{
    vec_texture_uptr.push_back(std::make_unique<TextureObject>(textureObject));
}

glm::mat4& RenderObject::getModelMatrix()
{
    return modelMatrix;
}

void RenderObject::setModelMatrix(const glm::mat4 &model)
{
    modelMatrix = model;
}

void RenderObject::setModelTimesMat(const glm::mat4 &mat)
{
    modelMatrix = modelMatrix * mat;
}

void RenderObject::render(const unsigned int shaderProgram_id, const CameraObject& camera)
{
    //TODO optimize when to multiply by modelMatrix. Only multiply when changed.

    glm::mat4x4 mvp = camera.getProjectionMatrix() * (camera.getViewMatrix() * modelMatrix);

    // set uniform MVP
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram_id, "mvp"), 1, GL_FALSE, glm::value_ptr(mvp));

    int count(0);
    // Empty texture
    glBindTexture(GL_TEXTURE_2D, 0);
    for (auto texture_it = vec_texture_uptr.begin(); texture_it != vec_texture_uptr.end(); ++texture_it, count += 1) {
        if (*texture_it) {
            // Set active texture
            glActiveTexture(GL_TEXTURE0 + count);
            // Bind texture to active texture
            glBindTexture(GL_TEXTURE_2D, (*texture_it)->getTexture());
        }
    }
    
    // Bind vertex array to VAO member int
    glBindVertexArray(VAO);
    
    // Draw data
    glDrawElements(GL_TRIANGLES, EBO_size, GL_UNSIGNED_INT, 0);
    
    // Unbind VAO
    glBindVertexArray(0);
}
