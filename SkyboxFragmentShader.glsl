#version 330 core

out vec4 fragColor;
in vec3 texCoords;

uniform samplerCube cubeMapTexture;

void main()
{
	fragColor = texture(cubeMapTexture,texCoords);
	//gl_FragDepth = 1.0; // evtl. 0.99 statt 1.0f
}
