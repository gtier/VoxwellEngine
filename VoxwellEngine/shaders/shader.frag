#version 330 core
out vec4 fragment_color;

//ENGINE NEEDS THESE UNIFORMS. DO NOT DELETE OR AUGMENT.
uniform sampler2D user_texture_0;
uniform sampler2D user_texture_1;
uniform sampler2D user_texture_2;
uniform sampler2D user_texture_3;
uniform sampler2D user_texture_4;
uniform sampler2D user_texture_5;
uniform sampler2D user_texture_6;
uniform sampler2D user_texture_7;
//

in vec3 pos;
in vec2 uv;
in vec3 normal;


void main()
{
    vec3 light = vec3(0.0, 10000.0, 0.0);
    vec3 pos_to_light = light - pos;
    pos_to_light = normalize(pos_to_light);

    float fraction_of_light = dot(pos_to_light, normal);
//    fragment_color = vec4(0.5, 0.22 + fraction_of_light * 0.78, 0.01, 1.0);
    fragment_color = vec4(normal, 1.0);
}
