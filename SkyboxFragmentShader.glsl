#version 330 core

out vec4 fragColor;
in vec3 texCoords;

uniform samplerCube cubeMapTexture;

void main()
{
	fragColor = texture(cubeMapTexture,texCoords);
}
