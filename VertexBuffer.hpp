#pragma once
#include <vector>
#include "Vertex.hpp"
#include "UniqueResource.hpp"

class VertexBuffer
{
public:
	VertexBuffer(const std::vector<Vertex> vertices);
	void bind();


private:
	static GLuint createVertexArrayObject();
	static void deleteVertexArrayObject(GLuint id);

	static GLuint createVertexBuffer();
	static void deleteVertexBuffer(GLuint id);

	UniqueResource m_vao{ createVertexArrayObject(),&deleteVertexArrayObject };
	UniqueResource m_vbo{createVertexBuffer(), &deleteVertexBuffer};
};

