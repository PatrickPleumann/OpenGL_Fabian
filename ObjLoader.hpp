#pragma once
#include <vector>
#include "glm/glm.hpp"

class ObjLoader
{
	bool loadOBJ(
		const char* path,
		std::vector<glm::vec3>& _vertices,
		std::vector<glm::vec3>& _normal,
		std::vector<glm::vec2>& _uvs
	);
};

