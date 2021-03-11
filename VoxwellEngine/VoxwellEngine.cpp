//
// Created by Griffin Dunaif on 3/10/21.
//

#include "VoxwellEngine.h"

VoxwellEngine::VoxwellEngine(int width, int height, Shader& vertex_shader, Shader& fragment_shader)
: _shader_program(vertex_shader, fragment_shader){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE); //This line is required for mac computers
    _engine_window = glfwCreateWindow(width, height, "MaxwellEngine", NULL, NULL);

    if (_engine_window == NULL) {
        glfwTerminate();
        throw VoxwellError("VoxwellEngine constructor: failed to init GLFW window");
    }

    glfwMakeContextCurrent(_engine_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) //Get OS specific functions
    {
        throw VoxwellError("VoxwellEngine constructor: failed to init GLAD");
    }

    glViewport(0, 0, width, height);

    glfwSetFramebufferSizeCallback(_engine_window, frame_resize);

    // Get rid of cursor
    glfwSetInputMode(_engine_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Set up shaders
    // build shaders
    _shader_program.build();
    // user shader program
    _shader_program.use();

    //Enable depth buffer
    glEnable(GL_DEPTH_TEST);
}

void VoxwellEngine::frame_resize(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void VoxwellEngine::start_render_loop() {
    while(!glfwWindowShouldClose(_engine_window))
    {
        render_frame();
    }
}

void VoxwellEngine::render_frame() {
    // Clear buffers
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Color that clear color uses
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clears color and depth buffer

    // GLFW uses two buffers so swap to render next frame
    glfwSwapBuffers(_engine_window);
    // Check for user input
    glfwPollEvents();
}
