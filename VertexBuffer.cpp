#include "VertexBuffer.hpp"

VertexBuffer::VertexBuffer(const std::vector<Vertex> vertices)
{
	glBindVertexArray(*m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, *m_vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(0)); // pos
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(sizeof(glm::vec3)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void VertexBuffer::bind()
{
	glBindVertexArray(*m_vao);
}

GLuint VertexBuffer::createVertexArrayObject()
{
	GLuint id;
	glGenVertexArrays(1, &id);
	return id;
}

void VertexBuffer::deleteVertexArrayObject(GLuint id)
{
	glDeleteVertexArrays(1, &id);
}

GLuint VertexBuffer::createVertexBuffer()
{
	GLuint id;
	glGenBuffers(1, &id);
	return id;
}


void VertexBuffer::deleteVertexBuffer(GLuint id)
{
	glDeleteBuffers(1, &id);
}
