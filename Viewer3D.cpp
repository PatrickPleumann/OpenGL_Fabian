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
	Mesh triangle = MeshData::getTriangle();
	m_triangle = Model
	{
		.m_vertexBuffer = VertexBuffer {triangle.vertices },
		.m_modelTransform = glm::scale(glm::vec3{ 0.5f,0.5f,1.0f }) * glm::translate(glm::vec3{ 0.0f,0.0f,-2.0f })
	};

	Mesh quad = MeshData::getQuad();
	m_quad = Model
	{
		.m_vertexBuffer = VertexBuffer { quad.vertices, quad.indices },
		.m_modelTransform = glm::translate(glm::vec3{ 2.0f,0.0f,0.0f })
	};

	Mesh cube = MeshData::getCube();
	m_cube = Model
	{
		.m_vertexBuffer = VertexBuffer{cube.vertices, cube.indices},
		.m_modelTransform = glm::translate(glm::vec3{0.0f,0.0f,0.0f})
	};

	Shader vertexShader("VertexShader.glsl", GL_VERTEX_SHADER);
	Shader fragmentShader("FragmentShader_Phong.glsl", GL_FRAGMENT_SHADER);
	shaderProgram = ShaderProgram(vertexShader, fragmentShader);

	m_texture = Texture(".\\assets\\Treebark_Normal.jpg");  //ein Punkt bei gleicher Ordner Ebene .. bei ein Ordner darüber (in jedem Fall relationell)

	m_skyBox = Skybox();
}

void Viewer3D::onUpdate(float deltaTime)
{
	handleInput(deltaTime);

	const auto winSize = getWindowSize();
	const float aspectRatio = winSize.x / winSize.y;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (shaderProgram)
	{
		shaderProgram->use();
		shaderProgram->addCameraTransform(m_camera.getViewTransform(), m_camera.calcProjectionTransform(aspectRatio), m_camera.position);

		//if (m_triangle)
		//{
		//	m_triangle->m_vertexBuffer.bind();
		//	shaderProgram->setModelTransform(m_triangle->m_modelTransform);
		//	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_triangle->m_vertexBuffer.getIndexCount()), GL_UNSIGNED_INT, 0);

		//}

		//if (m_quad)
		//{
		//	m_quad->m_vertexBuffer.bind();
		//	shaderProgram->setModelTransform(m_quad->m_modelTransform);
		//	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_quad->m_vertexBuffer.getIndexCount()), GL_UNSIGNED_INT, 0);

		//}
		if (m_cube)
		{
			m_cube->m_vertexBuffer.bind();
			shaderProgram->setModelTransform(m_cube->m_modelTransform);
			m_cube->m_modelTransform = glm::rotate(m_cube->m_modelTransform, glm::radians(20 * deltaTime), glm::vec3{ 0.0f,1.0f,0.0f });
			if (m_texture)
			{
				m_texture->bind(*shaderProgram, "baseColorTexture", 0);
			}
			glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_cube->m_vertexBuffer.getIndexCount()), GL_UNSIGNED_INT, 0);
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

	glm::vec2 mousePos = getMousePos();

	if (!m_lastMousePos)
	{
		m_lastMousePos = mousePos;
	}
	const float angularSpeed = { 20.0f };
	//lock to window on click!!!
	if (getMouseButton(0))    // to only move when left mouse button is clicked!
	{
		auto offset = *m_lastMousePos - mousePos;
		m_camera.yaw += offset.x * deltaTime * angularSpeed;
		m_camera.pitch += offset.y * deltaTime * angularSpeed;

		m_camera.pitch = glm::clamp(m_camera.pitch, -89.0f, 89.0f);
	}
	m_lastMousePos = mousePos;
}

