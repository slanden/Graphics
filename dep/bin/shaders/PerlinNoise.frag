#version 330 core
in vec3 Normals;
in vec2 TexCoord;
out vec4 color;

uniform sampler2D noiseTex;

void main()
{
	color = texture(noiseTex, TexCoord).rrrr;//vec4(Normals * 0.5f + 0.5f, 1.0f);
	color.a = 1;
}