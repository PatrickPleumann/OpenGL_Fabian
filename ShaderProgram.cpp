#include "ShaderProgram.hpp"
#include "Shader.hpp"
#include "glad/glad.h"

ShaderProgram::ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader)
	: m_id{ glCreateProgram(), [](GLuint id) { glDeleteProgram(id); } }
{
	glAttachShader(*m_id, vertexShader.get());
	glAttachShader(*m_id, fragmentShader.get());

	glLinkProgram(*m_id);

	glDetachShader(*m_id, vertexShader.get());
	glDetachShader(*m_id, fragmentShader.get());
}

void ShaderProgram::use() const
{
	glUseProgram(*m_id);
}
