//
// Created by Griffin Dunaif on 3/10/21.
//

#ifndef FINAL_PROJECT_SHADER_H
#define FINAL_PROJECT_SHADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>

using namespace std;

class Shader {
public:
    Shader(string file_path);

    const char *contents();
private:
    unique_ptr<string> _file_contents;
};


#endif //FINAL_PROJECT_SHADER_H
