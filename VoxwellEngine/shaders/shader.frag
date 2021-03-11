#version 330 core
in vec3 pos;
in vec2 uv;
in vec3 normal;

out vec4 fragment_color;

void main()
{
    fragment_color = vec4(1.0, 1.0, 1.0, 1.0);
}
