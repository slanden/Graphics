#version 410 core
layout (location = 0) in vec4 position;
layout (location = 1) in vec2 texcoord;
layout (location = 2) in vec3 normals;

out vec3 Normals;
out vec2 TexCoord;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;

uniform sampler2D noiseTex;
uniform float heightScale = 2;

void main()
{
    Normals = normals;
	TexCoord = texcoord;

	//sample height
	float height = texture(noiseTex, TexCoord).r * 5;

	//offset Y by the height and heightscale
	gl_Position = Projection * View * Model * (position + vec4(0, height * heightScale, 0, 0));
}