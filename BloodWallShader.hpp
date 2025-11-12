#pragma once
#include "UniqueResource.hpp"
#include "Shader.hpp"
#include "glm/glm.hpp"
#include "Camera.hpp"

class BloodWallShader
{
	public:

		//will 2 Shader haben um erzeugt zu werden. Die "GLuint" ID ist eine UniqueResource
		BloodWallShader(const Shader& vertexShader, const Shader& fragmentShader);

		void use() const;

		void addCameraTransform(const glm::mat4& viewTransform, const glm::mat4& projectionTransform, const glm::vec3& cameraPos);

		void setModelTransform(const glm::mat4& modelTransform);

		GLuint get() const
		{
			return *m_id;
		}

	private:

		UniqueResource m_id;

		GLuint m_viewTransformId;
		GLuint m_projectionTransformId;
		GLuint m_timeId;

		GLuint m_modelTransformId;
		GLuint m_cameraPos;
};

