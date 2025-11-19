#version 330 core

out vec4 FragColor;
in vec2 texCoords;

uniform sampler2D screenTexture;

void main()
{
	vec2 pixel = floor(texCoords * 128);
	FragColor = texture(screenTexture, pixel / 128); //+ 0.005*vec2( sin(1920.0*texCoords.x),cos(1080.0*texCoords.y)));
}