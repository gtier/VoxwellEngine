#version 330 core
layout (location = 0) in vec3 in_pos;
layout (location = 1) in vec2 in_uv;
layout (location = 2) in vec3 in_normal;

// MVP matrix
uniform mat4 mvp;

out vec3 pos;
out vec2 uv;
out vec3 normal;

void main()
{
    gl_Position = mvp * vec4(in_pos, 1.0);
    pos = in_pos;
    uv = in_uv;
    normal = in_normal;
}