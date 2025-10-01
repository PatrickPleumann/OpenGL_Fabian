#include "glad/glad.h"
#include "ShaderProgram.hpp"
#include "Shader.hpp"


ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader)
: m_id{ glCreateProgram(), [](GLuint id) {glDeleteProgram(id); } }
{
	glAttachShader(*m_id, vertexShader.get());
	glAttachShader(*m_id, fragmentShader.get());

	glLinkProgram(*m_id);

	glDetachShader(*m_id, vertexShader.get());
	glDetachShader(*m_id, fragmentShader.get());
}