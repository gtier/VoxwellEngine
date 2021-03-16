//
// Created by Griffin Dunaif on 3/10/21.
//

#ifndef FINAL_PROJECT_VOXWELLENGINE_H
#define FINAL_PROJECT_VOXWELLENGINE_H

#include "ves.h"
#include <iostream>
#include <iterator>
#include "Shader.h"
#include "ShaderProgram.h"
#include "RenderObject.hpp"
#include "CameraObject.hpp"
using namespace std;

// Manages the voxel engine
class VoxwellEngine {
public:
    VoxwellEngine(int width, int height, Shader& vertex_shader, Shader& fragment_shader);

    static void frame_resize(GLFWwindow* window, int width, int height);

    void start_render_loop();

    void render_frame();

    template <class T>
    size_t create_render_object(VertexDataObject<T>& vdo, vector<unsigned int>& indices);

    RenderObject& get_render_object(size_t id);

    static void cursor_handler(GLFWwindow* window, double x, double y);

private:
    GLFWwindow* _engine_window;
    ShaderProgram _shader_program;
    vector<unique_ptr<RenderObject>> _render_objects;
    vector<unique_ptr<RenderObject>>::iterator _open_container;
    float _last_frame_time;
    float _current_frame_time;
    float _delta_frame_time;
};


#endif //FINAL_PROJECT_VOXWELLENGINE_H
