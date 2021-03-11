//
// Created by Griffin Dunaif on 3/10/21.
//

#ifndef FINAL_PROJECT_SHADERPROGRAM_H
#define FINAL_PROJECT_SHADERPROGRAM_H

#include "ves.h"
#include "Shader.h"

class ShaderProgram {
private:
    const char * _vertex_contents;
    const char * _fragment_contents;
    unsigned int _id;
    bool _built = false;

public:
    ShaderProgram(Shader& vertex_shader, Shader& fragment_shader)
            : _vertex_contents(vertex_shader.contents()), _fragment_contents(fragment_shader.contents()), _id(0)
    {
    }

    void use() {
        glUseProgram(_id);
    }

    unsigned int get_id()
    {
        return _id;
    }

    //Pass in args and specific glUniform set function from OpenGL (e.g. glUniform1i or glUniform2f)
    template<class F, typename... Args>
    void setUniform(std::string name, F glFunc, Args... args) {
        if (!_built)
        {
            throw VoxwellError("ShaderProgram setUniform: shader not built");
        }
        try {
            glFunc(glGetUniformLocation(_id, name.c_str()), args...);
        } catch (std::exception&  e) {
            throw e;
        }

    }

    unsigned int build();
};


#endif //FINAL_PROJECT_SHADERPROGRAM_H
