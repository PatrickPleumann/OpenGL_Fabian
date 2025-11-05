#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec4 col;
layout (location = 2) in vec3 nor;
layout (location = 3) in vec2 uvsVertex;

out vec4 color;
out vec2 uvs;
out vec3 normal;
out vec3 vertexPos;

uniform mat4 modelTransform;
uniform mat4 viewTransformation;
uniform mat4 projectionTransformation;

void main()
{ 
	//matrices which stands on the very right is the first one to be multiplicated
	gl_Position = projectionTransformation * viewTransformation * modelTransform * vec4(pos, 1.0);
	uvs = uvsVertex;
	color = col;
	normal = vec3(transpose(inverse(modelTransform)) * vec4(nor, 1.0));
	vertexPos = vec3(modelTransform * vec4(pos.xyz, 1.0));
}