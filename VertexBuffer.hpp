#pragma once
#include <vector>
#include "Vertex.hpp"
#include "UniqueResource.hpp"

class VertexBuffer
{
public:
	VertexBuffer(const std::vector<Vertex>& vertices);
	VertexBuffer(const std::vector<Vertex> vertices, const std::vector<unsigned int> indices);
	void bind();

	size_t getIndexCount() const
	{
		return m_indexCount;
	}


private:
	static GLuint createVertexArrayObject();
	static void deleteVertexArrayObject(GLuint id);

	static GLuint createBuffer();
	static void deleteBuffer(GLuint id);

	UniqueResource m_vao{ createVertexArrayObject(), &deleteVertexArrayObject };
	UniqueResource m_vbo{ createBuffer(), &deleteBuffer};
	UniqueResource m_ebo{ createBuffer(), &deleteBuffer};
	bool m_hasIndexBuffer{ false };

	size_t m_indexCount{  };
};

