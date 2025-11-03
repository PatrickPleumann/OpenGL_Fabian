#version 330 core
in vec4 color;
in vec2 uvs;

out vec4 fragColor;

void main()
{
	fragColor = color /* * (1 - step(0.5,length(uvs)))*/;
}

