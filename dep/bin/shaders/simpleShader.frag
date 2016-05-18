#version 330 core
in vec3 Normals;
out vec4 color;

void main()
{
	color = vec4(Normals * 0.5f + 0.5f, 1.0f);
}