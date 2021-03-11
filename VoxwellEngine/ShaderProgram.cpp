//
// Created by Griffin Dunaif on 3/10/21.
//

#include "ShaderProgram.h"

unsigned int ShaderProgram::build() {
    if (_built) {
        throw VoxwellError("ShaderProgram build: program already built");
    } else {
        _built = true;
    }

    unsigned int vertShader = 0;
    vertShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertShader, 1, &_vertex_contents, NULL);
    glCompileShader(vertShader);

    int compileSuccess;
    char compileInfoLog[512];
    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &compileSuccess);

    if (!compileSuccess)
    {
        glGetShaderInfoLog(vertShader, 512, NULL, compileInfoLog);
        stringstream err;
        err << "ShaderProgram build: vertex shader failed to compile - " << compileInfoLog;
        throw VoxwellError(err.str());
    }

    unsigned int fragmentShader = 0;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &_fragment_contents, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compileSuccess);

    if (!compileSuccess)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, compileInfoLog);
        stringstream err;
        err << "ShaderProgram build: fragment shader failed to compile - " << compileInfoLog;
        throw VoxwellError(err.str());
    }

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int linkSuccess;
    char linkInfoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkSuccess);

    if (!linkSuccess)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, linkInfoLog);
        stringstream err;
        err << "ShaderProgram build: program failed to link - " << compileInfoLog;
        throw VoxwellError(err.str());
    }

    glDeleteShader(vertShader);
    glDeleteShader(fragmentShader);

    _id = shaderProgram;
    return shaderProgram;
}
