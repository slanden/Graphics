#version 330 core
layout (location = 0) in vec4 position;
layout (location = 1) in vec2 texcoords;
layout (location = 2) in vec3 normals;

out vec3 Normals;
uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;

void main()
{
    gl_Position = Projection * View * Model *  position;
    Normals = normals;
}