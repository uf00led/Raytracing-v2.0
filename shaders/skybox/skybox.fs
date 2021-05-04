#version 430 core

in  vec3 texture_coordinates;
out vec4 texture_out_color;

uniform samplerCube skybox;

void main()
{    
    texture_out_color = texture(skybox, texture_coordinates);
}