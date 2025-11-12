#include "BloodWallShader.hpp"
#include "GLFW/glfw3.h"

BloodWallShader::BloodWallShader(const Shader& vertexShader, const Shader& fragmentShader)
	: m_id{ glCreateProgram(), [](GLuint id) { glDeleteProgram(id); } }
{
	glAttachShader(*m_id, vertexShader.get());
	glAttachShader(*m_id, fragmentShader.get());

	glLinkProgram(*m_id);

	glDetachShader(*m_id, vertexShader.get());
	glDetachShader(*m_id, fragmentShader.get());

	m_viewTransformId = glGetUniformLocation(*m_id, "viewTransformation");
	m_projectionTransformId = glGetUniformLocation(*m_id, "projectionTransformation");

	m_modelTransformId = glGetUniformLocation(*m_id, "modelTransform");
	m_cameraPos = glGetUniformLocation(*m_id, "viewPos");

	m_timeId = glGetUniformLocation(*m_id, "time");
}

void BloodWallShader::use() const
{
	glUseProgram(*m_id);
}

void BloodWallShader::addCameraTransform(const glm::mat4& viewTransform, const glm::mat4& projectionTransform, const glm::vec3& cameraPos)
{
	glUniformMatrix4fv(m_viewTransformId, 1, GL_FALSE, &viewTransform[0][0]);
	glUniformMatrix4fv(m_projectionTransformId, 1, GL_FALSE, &projectionTransform[0][0]);
	glUniform3f(m_cameraPos, cameraPos.x, cameraPos.y, cameraPos.z);
	glUniform1f(m_timeId, static_cast<float>(glfwGetTime()));
}

void BloodWallShader::setModelTransform(const glm::mat4& modelTransform)
{
	glUniformMatrix4fv(m_modelTransformId, 1, GL_FALSE, &modelTransform[0][0]);
}