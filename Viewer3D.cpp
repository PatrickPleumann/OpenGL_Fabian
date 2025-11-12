#include "Viewer3D.hpp"
#include "glad/glad.h"
#include "Shader.hpp"
#include  <vector>
#include "Vertex.hpp"
#include "Mesh.hpp"
#include "Model.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "ObjectLoader.hpp"


void Viewer3D::onCreate()
{
	ObjectLoader OBJ;
	OBJ.LoadObjVertFromFile(OBJ.m_objFilePath, mesh.vertices, mesh.indices);
	GameObject* obj = new GameObject(0.0f,0.0f,20.0f, aspectRatio, m_camera, mesh);
	gameObjects.push_back(obj);

	m_skyBox = Skybox();
}


void Viewer3D::onUpdate(float deltaTime)
{
	const auto winSize = getWindowSize();
	aspectRatio = winSize.x / winSize.y;

	handleInput(deltaTime);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	RenderGameObjects(deltaTime);

	if (m_skyBox)
	{
		glDepthMask(GL_FALSE);
		m_skyBox->draw(m_camera);
		glDepthMask(GL_TRUE);
	}
}

//on window Resize event to re-calculate aspect ratio
void Viewer3D::handleInput(float deltaTime)
{
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
		m_camera.position += glm::normalize(m_camera.down) * deltaTime * speed;
	}

	if (getKey(GLFW_KEY_LEFT_CONTROL))
	{
		m_camera.position += -glm::normalize(m_camera.down) * deltaTime * speed;
	}

	if (getKey(GLFW_KEY_G))
	{ // woohoo endless spawning
		GameObject* obj = new GameObject((float)0 + rand() % 8, (float)0 + rand() % 8, (float)0 + rand() % 8, aspectRatio, m_camera);
		gameObjects.push_back(obj);
	}

	glm::vec2 mousePos = getMousePos();

	if (!m_lastMousePos)
	{
		m_lastMousePos = mousePos;
	}


	if (getMouseButton(0))    // to only move when left mouse button is clicked!
	{
		auto offset = *m_lastMousePos - mousePos;
		m_camera.yaw += -offset.x * deltaTime * angularSpeed;                             
		m_camera.pitch += offset.y * deltaTime * angularSpeed;

		m_camera.pitch = glm::clamp(m_camera.pitch, -89.0f, 89.0f);
	}
	m_lastMousePos = mousePos;
}

void Viewer3D::RenderGameObjects(float _deltaTime)
{
	for (auto gameObj : gameObjects)
	{
		InitializeGameObjects(*gameObj, aspectRatio, _deltaTime);
	}
}

void Viewer3D::InitializeGameObjects(GameObject& _obj, float _ascectRatio, float _deltaTime)
{
	if (!_obj.shaderProgram) return;

	_obj.shaderProgram->use();
	_obj.shaderProgram->addCameraTransform(m_camera.getViewTransform(), m_camera.calcProjectionTransform(_ascectRatio), m_camera.position);

	if (!_obj.model) return;

	_obj.model->m_vertexBuffer.bind();
	_obj.shaderProgram->setModelTransform(_obj.model->m_modelTransform);
	//_obj.model->m_modelTransform = glm::rotate(_obj.model->m_modelTransform, glm::radians(20 * _deltaTime), glm::vec3{ 1.0f,1.0f,1.0f });
	_obj.model->m_modelTransform = glm::rotate(_obj.model->m_modelTransform, glm::radians(20 *  _deltaTime), glm::vec3{ 0.0f,1.0f,0.0f });
	if (_obj.texture)
	{
		_obj.texture->bind(*_obj.shaderProgram, "cracksTexture", 0);
		_obj.texture2->bind(*_obj.shaderProgram, "normalTexture", 1);
	}
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(_obj.model->m_vertexBuffer.getIndexCount()), GL_UNSIGNED_INT, 0);

}


