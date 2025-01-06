#version 330 core
layout (location = 0) out vec4 color;

in vec3 pointColor;

void main()
{
    color = vec4(pointColor.x, pointColor.y, pointColor.z, 1.0);
}
