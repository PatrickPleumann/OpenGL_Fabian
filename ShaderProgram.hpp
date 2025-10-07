#pragma once
#include "UniqueResource.hpp"
#include "Shader.hpp"
#include "glm/glm.hpp"

class ShaderProgram
{
public:
	ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader);
	void use() const;

	void addCameraTransform(const glm::mat4& viewTransform, const glm::mat4& projectionTransform);
	void setModelTransform(const glm::mat4& modelTransform);
private:
	UniqueResource m_id;

	GLuint m_viewTransformId;
	GLuint m_projectionTransformId;

	GLuint m_modelTransformId;
};
	
