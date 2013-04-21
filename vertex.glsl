#version 150 core

uniform sampler2D uTexture;

in vec3 position;
in vec2 texCoord;

out vec2 texc;

void main()
{
	texc = texCoord;

	gl_Position = vec4(position, 1.0f);
}
