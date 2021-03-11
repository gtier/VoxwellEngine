//
// Created by Griffin Dunaif on 3/10/21.
//

#include "Shader.h"

Shader::Shader(string file_path) {
    ifstream file(file_path);
    stringstream string_stream;
    string_stream << file.rdbuf();
    file.close();

    _file_contents = make_unique<string>(string_stream.str());
}

const char* Shader::contents() {
    return _file_contents->c_str();
}