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
#include "VoxwellEngine/Biome.h"

bool pop_func(glm::ivec3 v_world_space_location) {
    int x = v_world_space_location.x;
    int y = v_world_space_location.y;
    int z = v_world_space_location.z;

    if ((x*x + y*y + z*z) < 256) {
        return true;
    }

    if (y < 4) {
        return true;
    }

    return false;
}

bool pop_func1(glm::ivec3 v_world_space_location) {
    return true;
}

int main() {
    Shader vertex_shader("/Users/griffin/Stanford/LOA/winter/CS 248/final project/VoxwellEngine/shaders/shader.vert");
    Shader fragment_shader("/Users/griffin/Stanford/LOA/winter/CS 248/final project/VoxwellEngine/shaders/shader.frag");

    VoxwellEngine engine(1280, 720, vertex_shader, fragment_shader);

//    Chunk c(glm::ivec3(-16, -10, -32), 32, 32, 32);
//    c.set_world_space_mapping(pop_func);
//    c.populate();
//    c.render(engine);

//    DiscWorld disc_world(glm::ivec3(0, 0, 0), glm::ivec3(0, 1, 0), 10);

    Biome biome(glm::ivec3(0, 0, 0), glm::ivec3(16, 16, 16), glm::ivec2(4, 4));
    biome.set_world_space_mapping(pop_func1);
    biome.populate();
    biome.render(engine);

    engine.start_render_loop();

    return 0;
}
