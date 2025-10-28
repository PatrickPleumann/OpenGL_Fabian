#version 330 core

layout (location = 0) in vec3 pos;

out vec3 texCoords;

uniform mat4 viewTransformation;
uniform mat4 projectionTransformation;

void main()
{
	texCoords = pos;
	gl_Position = (projectionTransformation * viewTransformation * vec4(pos, 1.0)).xyww;
}