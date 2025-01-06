#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 aColor;
out vec3 pointColor;

uniform vec2 screenSize;

void main()
{
    gl_Position = vec4(
      (position.x / screenSize.x - 0.5f) * 2.0f, 
      (position.y / screenSize.y - 0.5f) * 2.0f, 
      position.z, 1.0f
    );
    pointColor = aColor;
}
