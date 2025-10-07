#include "Viewer3D.hpp"
#include "glad/glad.h"
#include "Shader.hpp"
#include  <vector>
#include "Vertex.hpp"


void Viewer3D::onCreate()
{
	std::vector<Vertex> vertices
	{
		Vertex{.pos = {-0.5f, -0.5f, 0.0f},.color = {1.0f,0.0f,0.0f,1.0f}},
		Vertex{.pos = {0.5f, -0.5f, 0.0f},.color = {0.0f,1.0f,0.0f,1.0f}},
		Vertex{.pos = {0.0f, 0.5f, 0.0f},.color = {0.0f,0.0f,1.0f,1.0f}}
	};

	vertexBuffer = VertexBuffer{ vertices };

	Shader vertexShader("VertexShader.glsl", GL_VERTEX_SHADER);
	Shader fragmentShader("FragmentShader.glsl", GL_FRAGMENT_SHADER);
	shaderProgram = ShaderProgram(vertexShader, fragmentShader);

}

void Viewer3D::onUpdate(float deltaTime)
{
	handleInput(deltaTime);

	glClear(GL_COLOR_BUFFER_BIT);

	if (shaderProgram && vertexBuffer)
	{
		vertexBuffer->bind();
		shaderProgram->use();

		shaderProgram->addCameraTransform(m_camera.getViewTransform(), m_camera.m_projectionTransform);
		shaderProgram->setModelTransform(glm::scale(glm::vec3{ 0.5f,0.5f,1.0f }) * glm::translate(glm::vec3{ 0.0f,0.0f,-2.0f }));
		glDrawArrays(GL_TRIANGLES, 0, 3);

		shaderProgram->setModelTransform(glm::translate(glm::vec3{ 1.0f,0.0f,-2.0f }));
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
}

void Viewer3D::handleInput(float deltaTime)
{
	const float speed = { 10.0f };
	if (getKey(GLFW_KEY_W))
	{
		m_camera.position += m_camera.direction * deltaTime * speed;
	}
	if (getKey(GLFW_KEY_S))
	{
		m_camera.position += -m_camera.direction * deltaTime * speed;
	}

	if (getKey(GLFW_KEY_A))
	{
		m_camera.position += glm::normalize(glm::cross( m_camera.up, m_camera.direction )) * deltaTime * speed;
	}

	if (getKey(GLFW_KEY_D))
	{
		m_camera.position += -glm::normalize(glm::cross( m_camera.up,m_camera.direction)) * deltaTime * speed;
	}
}
