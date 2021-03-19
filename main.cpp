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
#include "PerlinNoise/PerlinNoise.hpp"
#include "VoxwellEngine/Biomes/Overhang.h"
#include "VoxwellEngine/Biomes/Mountains.h"
#include "VoxwellEngine/Biomes/Desert.h"
#include "VoxwellEngine/Biomes/Tunnels.h"

int main() {
    Shader vertex_shader("/Users/griffin/Stanford/LOA/winter/CS 248/final project/VoxwellEngine/shaders/shader.vert");
    Shader fragment_shader("/Users/griffin/Stanford/LOA/winter/CS 248/final project/VoxwellEngine/shaders/shader.frag");

    VoxwellEngine engine(1280, 720, vertex_shader, fragment_shader);

//    Voxel v(glm::ivec3(0, 0, 0));
//    v.set_visibility(true);
//    v.render(engine);

//    Chunk c(glm::ivec3(0, 0, -40), 32, 32, 32);
//    c.populate();
//    c.render(engine);

//    DiscWorld disc_world(glm::ivec3(0, 0, 0), glm::ivec3(0, 1, 0), 10);


    // scene 1 start and scene 2 rgb
//    Overhang overhang(glm::ivec3(0, 0, 0), glm::ivec3(16, 32, 16), glm::ivec2(32, 32));
//    overhang.render(engine);
//    Desert desert1(glm::ivec3((32 * 16), 0, 0), glm::ivec3(16, 64, 16), glm::ivec2(32, 32));
//    desert1.render(engine);
//    Desert desert(glm::ivec3(0, 0, -(32 * 16)), glm::ivec3(16, 64, 16), glm::ivec2(32, 32));
//    desert.render(engine);
//    Tunnels tunnels(glm::ivec3(0, 0, 320), glm::ivec3(256, 256, 256), glm::ivec2(1, 1));
//    tunnels.render(engine);
    //scene 1 end

    // scene 2 start
//    Mountains mountains(glm::ivec3(0, 0, 0), glm::ivec3(512, 128, 512), glm::ivec2(1, 1));
//    mountains.render(engine);
    // scene 2 end

//    Desert desert(glm::ivec3(0, 0, 0), glm::ivec3(16, 64, 16), glm::ivec2(64, 64));
//    desert.render(engine);

    // scene 3 start
    Tunnels tunnels(glm::ivec3(0, 0, 0), glm::ivec3(256, 256, 256), glm::ivec2(1, 1));
    tunnels.render(engine);
    // scene 3 end

    engine.start_render_loop();

    return 0;
}
