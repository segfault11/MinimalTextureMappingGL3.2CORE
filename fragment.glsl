#version 150 core

uniform sampler2D uTexture;

in vec2 texc;
out vec4 fragOutput;

void main()
{
	vec4 col = vec4(1.0f, 0.0f, 0.0f, 1.0f)*texture(uTexture, texc.st).r;
    fragOutput = vec4(texture(uTexture, texc).rgb, 1.0f);
}
