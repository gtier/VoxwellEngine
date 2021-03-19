//
// Created by Griffin Dunaif on 3/10/21.
//

#include "VoxwellEngine.h"

static unique_ptr<CameraObject> _camera;

VoxwellEngine::VoxwellEngine(int width, int height, Shader& vertex_shader, Shader& fragment_shader)
: _shader_program(vertex_shader, fragment_shader), _open_container(_render_objects.end()){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE); //This line is required for mac computers
    _engine_window = glfwCreateWindow(width, height, "VoxwellEngine", NULL, NULL);

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

    //Set up camera
    _camera = make_unique<CameraObject>(width, height);

    glfwSetCursorPosCallback(_engine_window, cursor_handler);
}

void VoxwellEngine::frame_resize(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void VoxwellEngine::start_render_loop() {
    while(!glfwWindowShouldClose(_engine_window))
    {
        // get frame delta
        _current_frame_time = glfwGetTime();
        _delta_frame_time = _current_frame_time - _last_frame_time;
        _last_frame_time = _current_frame_time;

        // handle user interactions before render. Improvement on Maxwell
        _camera->keyHandler(_engine_window, _delta_frame_time);

        // render
        render_frame();
    }
}

void VoxwellEngine::render_frame() {
    // Clear buffers
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Color that clear color uses
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clears color and depth buffer

    for (auto& obj: _render_objects) {
        obj->render(_shader_program.get_id(), *_camera);
    }

    // GLFW uses two buffers so swap to render next frame
    glfwSwapBuffers(_engine_window);
    // Check for user input
    glfwPollEvents();
}

// Improved design of maxwell engine create_render_object
template <class T>
size_t VoxwellEngine::create_render_object(VertexDataObject<T>& vdo, vector<unsigned int>& indices) {
    size_t num_objects = _render_objects.size();
    size_t render_object_id = num_objects;

    auto render_object_ptr = make_unique<RenderObject>();
    render_object_ptr->init(vdo, indices.data(), indices.size() * sizeof(unsigned int));

    // No open containers
    if (_open_container == _render_objects.end()) {
        _render_objects.push_back(move(render_object_ptr));
        // update end of container
        _open_container = _render_objects.end();
    } else {
        // TODO fix this. Allow for multiple open containers
        _render_objects.insert(_open_container, move(render_object_ptr));
        render_object_id = distance(_render_objects.begin(), _open_container);
    }

    return render_object_id;
}

template size_t VoxwellEngine::create_render_object<float>(VertexDataObject<float> &vdo, vector<unsigned int> &indices);

RenderObject& VoxwellEngine::get_render_object(size_t id)
{
    return *_render_objects[id];
}

void VoxwellEngine::cursor_handler(GLFWwindow *window, double x, double y) {
    _camera->cursorHandler(window, x, y);
}
