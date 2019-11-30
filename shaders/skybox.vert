#version 330 core

layout (location = 0) in vec3 position;

uniform mat4 projection;
uniform mat4 view;

out vec3 vPos;// position in object space

void main()
{
    gl_Position = projection * view * vec4(position, 1.0);
    gl_Position = gl_Position.xyww;// infinity depth
    vPos = position;
}