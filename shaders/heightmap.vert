#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec3 vNormal;
out float vHeight;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0);
    vHeight = position.y;
    vNormal = transpose(inverse(mat3(model))) * normal;
}