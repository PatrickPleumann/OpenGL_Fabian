#include "Viewer3D.hpp"
#include "glad/glad.h"
#include "Shader.hpp"
#include  <vector>
#include "Vertex.hpp"
#include "Mesh.hpp"
#include "Model.hpp"
#include "glm/ext/matrix_transform.hpp"

void Viewer3D::onCreate()
{
	//Mesh cube = MeshData::getCube();
	//m_cube = Model
	//{
	//	.m_vertexBuffer = VertexBuffer{cube.vertices, cube.indices},
	//	.m_modelTransform = glm::translate(glm::vec3{0.0f,0.0f,0.0f})
	//};

	//Shader vertexShader("VertexShader.glsl", GL_VERTEX_SHADER);
	//Shader fragmentShader("FragmentShader_Phong.glsl", GL_FRAGMENT_SHADER);
	//shaderProgram = ShaderProgram(vertexShader, fragmentShader);

	m_skyBox = Skybox();
}

void Viewer3D::onUpdate(float deltaTime)
{
	handleInput(deltaTime);

	const auto winSize = getWindowSize();
	const float aspectRatio = winSize.x / winSize.y;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GameObject obj(0.0f, 0.0f, 0.0f, aspectRatio, m_camera);
	if (obj.shaderProgram)
	{
		obj.shaderProgram->use();
		obj.shaderProgram->addCameraTransform(m_camera.getViewTransform(), m_camera.calcProjectionTransform(aspectRatio), m_camera.position);

		if (obj.model)
		{
			obj.model->m_vertexBuffer.bind();
			obj.shaderProgram->setModelTransform(obj.model->m_modelTransform);
			obj.model->m_modelTransform = glm::rotate(obj.model->m_modelTransform, glm::radians(20 * deltaTime), glm::vec3{ 0.0f,1.0f,0.0f });
			if (obj.texture)
			{
				obj.texture->bind(*obj.shaderProgram, "baseColorTexture", 0);
			}
			glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(obj.model->m_vertexBuffer.getIndexCount()), GL_UNSIGNED_INT, 0);
		}
	}

	GameObject obj2(1.0f, 1.0f, 1.0f, aspectRatio, m_camera);
	if (obj2.shaderProgram)
	{
		obj2.shaderProgram->use();
		obj2.shaderProgram->addCameraTransform(m_camera.getViewTransform(), m_camera.calcProjectionTransform(aspectRatio), m_camera.position);

		if (obj2.model)
		{
			obj2.model->m_vertexBuffer.bind();
			obj2.shaderProgram->setModelTransform(obj2.model->m_modelTransform);
			obj2.model->m_modelTransform = glm::rotate(obj2.model->m_modelTransform, glm::radians(20 * deltaTime), glm::vec3{ 0.0f,1.0f,0.0f });
			if (obj2.texture)
			{
				obj2.texture->bind(*obj2.shaderProgram, "baseColorTexture", 0);
			}
			glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(obj2.model->m_vertexBuffer.getIndexCount()), GL_UNSIGNED_INT, 0);
		}
	}
	

	if (m_skyBox)
	{
		glDepthMask(GL_FALSE);
		m_skyBox->draw(m_camera);
		glDepthMask(GL_TRUE);
	}
}

void Viewer3D::handleInput(float deltaTime)
{
	const float speed = { 10.0f };

	//encapsulate GLWF_keys into separate class 
	if (getKey(GLFW_KEY_W))
	{
		m_camera.position += m_camera.getDirection() * deltaTime * speed;
	}
	if (getKey(GLFW_KEY_S))
	{
		m_camera.position += -m_camera.getDirection() * deltaTime * speed;
	}

	if (getKey(GLFW_KEY_A))
	{
		m_camera.position += glm::normalize(glm::cross(m_camera.up, m_camera.getDirection())) * deltaTime * speed;
	}

	if (getKey(GLFW_KEY_D))
	{
		m_camera.position += -glm::normalize(glm::cross(m_camera.up, m_camera.getDirection())) * deltaTime * speed;
	}
	if (getKey(GLFW_KEY_SPACE))
	{
		m_camera.position += -glm::normalize(glm::cross(m_camera.down, m_camera.getDirection())) * deltaTime * speed;
	}

	if (getKey(GLFW_KEY_LEFT_CONTROL))
	{
		m_camera.position += glm::normalize(glm::cross(m_camera.down, m_camera.getDirection())) * deltaTime * speed;
	}


	glm::vec2 mousePos = getMousePos();

	if (!m_lastMousePos)
	{
		m_lastMousePos = mousePos;
	}
	const float angularSpeed = { 20.0f };


	if (getMouseButton(0))    // to only move when left mouse button is clicked!
	{
		auto offset = *m_lastMousePos - mousePos;
		m_camera.yaw += offset.x * deltaTime * angularSpeed;
		m_camera.pitch += offset.y * deltaTime * angularSpeed;

		m_camera.pitch = glm::clamp(m_camera.pitch, -89.0f, 89.0f);
	}
	m_lastMousePos = mousePos;
}

