cmake_minimum_required(VERSION 3.19)
project(final_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3")

include_directories( "/System/Library/Frameworks" )
find_library (COCOA_LIBRARIES Cocoa)
find_library (IOKIT_LIBRARIES IOkit)
find_library (COREVIDEO_LIBRARIES CoreVideo)

find_package(OpenGL REQUIRED)
find_package(Threads REQUIRED)
find_package(Freetype REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLFW3 REQUIRED)
find_package(GLM REQUIRED)

include_directories("glad/include/")
include_directories("stb_image")

add_executable(final_project main.cpp glad.c glad/include/glad/glad.h glad/include/KHR/khrplatform.h
        VoxwellEngine/RenderObject.cpp VoxwellEngine/RenderObject.hpp VoxwellEngine/VertexDataObject.hpp
        VoxwellEngine/VertexAttribute.hpp VoxwellEngine/CameraObject.hpp
        VoxwellEngine/TextureObject.hpp VoxwellEngine/TextureObject.cpp
        stb_image/stb_image.h PerlinNoise/PerlinNoise.hpp
        VoxwellEngine/Shapes/3D/cube.hpp VoxwellEngine/Shapes/3D/cube.cpp
        VoxwellEngine/VoxwellEngine.cpp VoxwellEngine/VoxwellEngine.h VoxwellEngine/Shader.cpp VoxwellEngine/Shader.h VoxwellEngine/ShaderProgram.cpp VoxwellEngine/ShaderProgram.h VoxwellEngine/ves.h VoxwellEngine/Voxel.cpp VoxwellEngine/Voxel.h VoxwellEngine/Chunk.cpp VoxwellEngine/Chunk.h VoxwellEngine/DiscWorld.cpp VoxwellEngine/DiscWorld.h VoxwellEngine/Shapes/3D/face.cpp VoxwellEngine/Shapes/3D/face.h VoxwellEngine/VoxelFace.h VoxwellEngine/VoxelFace.cpp VoxwellEngine/Biome.cpp VoxwellEngine/Biome.h VoxwellEngine/Biomes/Mountains.cpp VoxwellEngine/Biomes/Mountains.h)

target_link_libraries(final_project glfw)
target_link_libraries(final_project OpenGL::GL)
target_link_libraries(final_project ${COCOA_LIBRARIES})
target_link_libraries(final_project ${IOKIT_LIBRARIES})
target_link_libraries(final_project ${COREVIDEO_LIBRARIES})