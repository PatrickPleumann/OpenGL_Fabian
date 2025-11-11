#pragma once
#include <vector>
#include "Vertex.hpp"
class Mesh
{
public:
	std::vector<Vertex> vertices; // siehe Vertex
	std::vector<unsigned int> indices;    // open gl standardmaessig gegen den Uhrzeigersinn
};

namespace MeshData
{
	//Mesh getTriangle();
	//Mesh getQuad();
	Mesh getCube();

	Mesh getCustomModel(); // start file dialog here for custom model
}


