#version 330 core
layout (location = 0) in vec4 position;
layout (location = 1) in vec3 aColor;
out vec3 pointColor;
void main()
{
    gl_Position = position;
    pointColor = aColor;
}