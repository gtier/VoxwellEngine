#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "VoxwellEngine/VoxwellEngine.h"
#include "VoxwellEngine/Shapes/3D/cube.hpp"

int main() {
    Shader vertex_shader("/Users/griffin/Stanford/LOA/winter/CS 248/final project/VoxwellEngine/shaders/shader.vert");
    Shader fragment_shader("/Users/griffin/Stanford/LOA/winter/CS 248/final project/VoxwellEngine/shaders/shader.frag");

    VoxwellEngine engine(800, 600, vertex_shader, fragment_shader);

    cube c;

    engine.start_render_loop();

    return 0;
}
