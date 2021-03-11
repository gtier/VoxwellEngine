//
// Created by Griffin Dunaif on 3/10/21.
//

#ifndef FINAL_PROJECT_VES_H
#define FINAL_PROJECT_VES_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <exception>

class VoxwellError: public std::exception {
public:
    explicit VoxwellError(std::string error)
    {
        _info = error;
    }

    const char* what() const throw()
    {
        return _info.c_str();
    }
private:
    std::string _info;
};

#endif //FINAL_PROJECT_VES_H
