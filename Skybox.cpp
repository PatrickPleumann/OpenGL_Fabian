#include "Skybox.hpp"
#include "Mesh.hpp"
#include <array>
#include "Image.hpp"
#include <ranges>
#include "ShaderProgram.hpp"
#include "Shader.hpp"

namespace
{
	const std::array<std::string, 6> c_imageNames
	{
		".\\assets\\Skybox\\right.jpg",
		".\\assets\\Skybox\\left.jpg",
		".\\assets\\Skybox\\top.jpg",
		".\\assets\\Skybox\\bottom.jpg",
		".\\assets\\Skybox\\front.jpg",
		".\\assets\\Skybox\\back.jpg"
	};
}

Skybox::Skybox()
{
	//Mesh cube
	Mesh cubeMesh = MeshData::getCube();
	m_model = Model
	{
		.m_vertexBuffer = VertexBuffer(cubeMesh.vertices, cubeMesh.indices),
		.m_modelTransform = glm::mat4(1.0)
	};
	//Bilder für Cubemap texture laden
	glBindTexture(GL_TEXTURE_CUBE_MAP, *m_texId);

	for (const auto& [i,filename] : std::views::enumerate(c_imageNames))
	{
		Image image{ filename, false };
		if (image.buffer)
		{
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

			glTexImage2D(static_cast<GLenum>(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i), 0, GL_RGBA8, image.width, image.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.buffer);

		}
	}
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	//Shader anlegen
	m_shaderProgram = ShaderProgram
	(
		Shader("SkyboxVertexShader.glsl", GL_VERTEX_SHADER),
		Shader("SkyboxFragmentShader.glsl", GL_FRAGMENT_SHADER)
	);
	
}

void Skybox::draw(const Camera& camera)
{
	// shader aktivieren
	if (!m_shaderProgram)
	{
		return;
	}
	m_shaderProgram->use();
	// cubemap texture aktivieren
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, *m_texId);

	m_model->m_vertexBuffer.bind();
	// würfel zeichnen (Innenflächen)
	GLint oldFaceMode;
	glGetIntegerv(GL_CULL_FACE_MODE, &oldFaceMode);
	glCullFace(GL_FRONT);

	GLint oldDepthMode;
	glGetIntegerv(GL_DEPTH_FUNC, &oldDepthMode);
	glDepthFunc(GL_LEQUAL);

	glm::mat4 viewTransform = glm::mat3(camera.getViewTransform());
	m_shaderProgram->addCameraTransform(viewTransform,camera.projectionTransform, camera.position);

	glDrawElements(GL_TRIANGLES, m_model->m_vertexBuffer.getIndexCount(), GL_UNSIGNED_INT, 0);

	glCullFace(oldFaceMode);
	glDepthFunc(oldDepthMode);
	//.. draw
}
