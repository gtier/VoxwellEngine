#version 330 core
out vec4 FragColor;

in vec2 uv;
in vec3 normal;
in vec3 vertexPos;

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

uniform vec3 lightPos = vec3(-150.0, 300.0, 100.0);

void main()
{
//  FragColor = texture(user_texture_0, uv);
    vec3 obj_color = vec3(1.0, 0.5, 0.25);
    vec3 norm = normalize(normal);
    vec3 diff = normalize(lightPos - norm);
    float dot_product = max(dot(diff, norm), 0.0);
    vec3 diffuse = dot_product * obj_color;
    vec3 output_val = diffuse;
    FragColor = vec4(output_val, 1.0);
} 
