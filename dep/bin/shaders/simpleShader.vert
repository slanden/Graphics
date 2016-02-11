#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec3 ourColor;
uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;

void main()
{
    gl_Position = Projection * View * Model *  vec4(position,1.0f);
    ourColor = vec3(1.0f, 0.5f, 0.2f);
}