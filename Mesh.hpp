#pragma once
#include <vector>
#include "Vertex.hpp"
class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
};

namespace MeshData
{
	Mesh getTriangle();

	Mesh getQuad();
}


