//
// Created by Griffin Dunaif on 3/10/21.
//

#ifndef FINAL_PROJECT_VOXWELLENGINE_H
#define FINAL_PROJECT_VOXWELLENGINE_H

#include "ves.h"
#include <iostream>
#include "Shader.h"
#include "ShaderProgram.h"
using namespace std;

// Manages the voxel engine
class VoxwellEngine {
public:
    VoxwellEngine(int width, int height, Shader& vertex_shader, Shader& fragment_shader);

    static void frame_resize(GLFWwindow* window, int width, int height);

    void start_render_loop();

    void render_frame();
private:
    GLFWwindow* _engine_window;
    ShaderProgram _shader_program;
};


#endif //FINAL_PROJECT_VOXWELLENGINE_H
