#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "MaxwellEngine/MaxwellEngine.hpp"
#include "MaxwellEngine/ShaderFile.hpp"

int main() {
    std::cout << "Hello, World!" << std::endl;
    glm::vec3 v(0.0, 0.0, 0.0);

    mes::ShaderFile vertexShaderFile("/Users/griffin/Documents/cpp-projects/MaxwellEngine/MaxwellEngine/Shaders/vertexShader.glsl");

    mes::ShaderFile fragmentShaderFile("/Users/griffin/Documents/cpp-projects/MaxwellEngine/MaxwellEngine/Shaders/fragmentShader.glsl");

    // Construct an engine instance with vertex and fragment shader
    mes::MaxwellEngine engine(vertexShaderFile, fragmentShaderFile);

    return 0;
}
