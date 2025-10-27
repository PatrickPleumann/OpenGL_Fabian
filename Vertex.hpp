#pragma once
#include "glm/glm.hpp"

struct Vertex
{
	glm::vec3 pos;
	glm::vec4 color;
	glm::vec3 normal{ 0.0f,0.0f,1.0f };
	glm::vec2 uvs;
};