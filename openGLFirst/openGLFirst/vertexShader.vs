#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 view;
uniform mat4 transform;
uniform vec4 aColor;

out vec4 color; 

void main()
{
    gl_Position = view * (transform * vec4(aPos, 1.0));
    //gl_Position = transform * vec4(aPos, 1.0f);
    color = aColor;
    //gl_Position = vec4(aPos, 1.0);
}