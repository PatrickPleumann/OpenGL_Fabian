#include "Mesh.hpp"

Mesh MeshData::getTriangle()
{
	std::vector<Vertex> vertices;

	Vertex{ .pos = {-0.5f, -0.5f, 0.0f},.color = {1.0f,0.0f,0.0f,1.0f} },
		Vertex{ .pos = {0.5f, -0.5f, 0.0f},.color = {0.0f,1.0f,0.0f,1.0f} },
		Vertex{ .pos = {0.0f, 0.5f, 0.0f},.color = {0.0f,0.0f,1.0f,1.0f} };

	return Mesh{ vertices };
};

Mesh MeshData::getQuad()
{

	std::vector<Vertex> vertices;

	Vertex{ .pos = {-0.5f, -0.5f, 0.0f},.color = {1.0f,0.0f,0.0f,1.0f} },
		Vertex{ .pos = {0.5f, -0.5f, 0.0f},.color = {0.0f,1.0f,0.0f,1.0f} },
		Vertex{ .pos = {0.5f, 0.5f, 0.0f},.color = {0.0f,0.0f,1.0f,1.0f} },
		Vertex{ .pos = {-0.5f,0.5f, 0.0f}, .color = {0.0f,1.0f,0.0f,1.0f}
	};

	std::vector<unsigned int> indices{ 0, 1, 2, 0 , 2 , 3 };

	return Mesh{ vertices, indices };
}