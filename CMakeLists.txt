cmake_minimum_required(VERSION 3.19)
project(final_project)

set(CMAKE_CXX_STANDARD 14)

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

add_executable(final_project main.cpp glad.c VoxwellEngine/VoxwellEngine.cpp VoxwellEngine/VoxwellEngine.h)

target_link_libraries(final_project glfw)
target_link_libraries(final_project OpenGL::GL)