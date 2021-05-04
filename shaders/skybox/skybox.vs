#version 430 core
layout (location = 0) in vec3 position;

out vec3 texture_coordinates;

uniform mat4 projection_matrix;
uniform mat4 view_matrix;

void main()
{
    texture_coordinates = position.xyz;
    gl_Position = projection_matrix * view_matrix * vec4(position, 1.0);
}  