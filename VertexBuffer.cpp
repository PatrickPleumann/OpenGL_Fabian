#include "VertexBuffer.hpp"
#include "Texture.hpp"

VertexBuffer::VertexBuffer(const std::vector<Vertex>& vertices)
{
	//VAO = Verkapselung und Zusammenfassung von VBO(vertices) & EBO(indices)
	glBindVertexArray(*m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, *m_vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, Vertex::pos))); // pos
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, Vertex::color)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2,3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex,Vertex::normal)));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, Vertex::uvs)));
	glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0); 
	// In Summe weiss die GraKa dann wo was ist im zu malenden Array 
}

VertexBuffer::VertexBuffer(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
	: VertexBuffer(vertices)
{
	m_hasIndexBuffer = true;
	m_indexCount = indices.size();
	glBindVertexArray(*m_vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


void VertexBuffer::bind()
{
	glBindVertexArray(*m_vao);
	if (m_hasIndexBuffer)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *m_ebo);
	}
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

GLuint VertexBuffer::createBuffer()
{
	GLuint id;
	glGenBuffers(1, &id);
	return id;
}


void VertexBuffer::deleteBuffer(GLuint id)
{
	glDeleteBuffers(1, &id);
}
