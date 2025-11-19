#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec4 col;
layout (location = 2) in vec3 nor;
layout (location = 3) in vec2 uvsVertex;
layout (location = 4) in vec3 tangents;
layout (location = 5) in vec3 bitangents;

out vec4 color;
out vec2 uvs;
out vec3 vertexPos;
out mat3 TBN;

uniform mat4 modelTransform;
uniform mat4 viewTransformation;
uniform mat4 projectionTransformation;

void main()
{ 
	//matrices which stands on the very right is the first one to be multiplicated
	gl_Position = projectionTransformation * viewTransformation * modelTransform * vec4(pos, 1.0);
	uvs = uvsVertex;
	color = col;

	vec3 normal = vec3(transpose(inverse(modelTransform)) * vec4(nor, 1.0));

	vec3 T = normalize(vec3(modelTransform * vec4(tangents,   0.0)));
	vec3 B = normalize(vec3(modelTransform * vec4(bitangents, 0.0)));
	vec3 N = normalize(vec3(modelTransform * vec4(normal,    0.0)));
	TBN = mat3(T, B, N);

	vertexPos = vec3(modelTransform * vec4(pos.xyz, 1.0));
}