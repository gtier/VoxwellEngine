
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 inUv;
layout (location = 2) in vec3 inNormal;

out vec4 outColor;
out vec2 uv;
out vec3 normal;
out vec3 vertexPos;

//ENGINE NEEDS THESE UNIFORMS. DO NOT DELETE OR AUGMENT.
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
//

void main()
{
    gl_Position = projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    uv = inUv;
    normal = inNormal;
    vertexPos = vec3(model * vec4(aPos, 1.0));
}
