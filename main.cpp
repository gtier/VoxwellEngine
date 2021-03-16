#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "VoxwellEngine/VoxwellEngine.h"
#include "VoxwellEngine/Shapes/3D/cube.hpp"
#include "VoxwellEngine/Voxel.h"
#include "VoxwellEngine/Chunk.h"
#include "VoxwellEngine/DiscWorld.h"

bool pop_func(long x, long y, long z) {
    if ((x*x + y*y + z*z) < 256) {
        return true;
    }

    if (y < 4) {
        return true;
    }

    return false;
}

int main() {
    Shader vertex_shader("/Users/griffin/Stanford/LOA/winter/CS 248/final project/VoxwellEngine/shaders/shader.vert");
    Shader fragment_shader("/Users/griffin/Stanford/LOA/winter/CS 248/final project/VoxwellEngine/shaders/shader.frag");

    VoxwellEngine engine(1280, 720, vertex_shader, fragment_shader);

    Chunk c(0, 0, 0, 32, 32, 32);
    c.set_world_space_mapping(pop_func);
    c.populate();
    c.render(engine);

    Chunk c1(0, 0, 32, 32, 32, 32);
    c1.set_world_space_mapping(pop_func);
    c1.populate();
    c1.render(engine);

    Chunk c2(-32, 0, 32, 32, 32, 32);
    c2.set_world_space_mapping(pop_func);
    c2.populate();
    c2.render(engine);

    Chunk c3(-32, 0, 0, 32, 32, 32);
    c3.set_world_space_mapping(pop_func);
    c3.populate();
    c3.render(engine);

    DiscWorld disc_world(glm::ivec3(0, 0, 0), glm::ivec3(0, 1, 0), 10);

    engine.start_render_loop();

    return 0;
}
