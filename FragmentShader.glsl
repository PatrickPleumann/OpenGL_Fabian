#version 330 core
out vec4 fragColor;
in vec4 color;
in vec2 uvs;

void main()
{
	fragColor = color /* * (1 - step(0.5,length(uvs)))*/;
}