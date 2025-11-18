#version 330 core

out vec4 FragColor;
in vec2 texCoords;

uniform sampler2D screenTexture;

void main()
{
	//FragColor = texture(screenTexture, texCoords);
	FragColor = texture( screenTexture, texCoords + 0.02*vec2( sin(1920.0*texCoords.x),cos(1080.0*texCoords.y)) ).xyz
	//FragColor = vec4(1.0,0.0,0.0,1.0);
}