#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec4 col;

out vec4 color;

uniform mat4 modelTransformation;
uniform mat4 viewTransformation;
uniform mat4 projectionTransformation;

void main()
{ //matrices which stands on the very right is the first one to be multiplicated
	gl_Position = projectionTransformation * viewTransformation * modelTransformation * vec4(pos, 1.0);
	color = col;
}