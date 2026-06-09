#include "Viewer3D.hpp"
#include "glad/glad.h"
#include "Shader.hpp"
#include  <vector>
#include "Vertex.hpp"
#include "Mesh.hpp"
#include "Model.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "ObjectLoader.hpp"
#include <iostream>
#include <cmath>

namespace
{
	// [BENCH] minimal shader: model matrix from instance attribute OR uniform (uInstanced switch)
	const char* k_benchVS = R"(#version 330 core
layout(location=0) in vec3 pos;
layout(location=2) in vec3 nor;
layout(location=6) in mat4 iModel;
uniform mat4 viewTransformation;
uniform mat4 projectionTransformation;
uniform mat4 uModel;
uniform int  uInstanced;
out vec3 vNormal;
void main()
{
	mat4 model = (uInstanced == 1) ? iModel : uModel;
	gl_Position = projectionTransformation * viewTransformation * model * vec4(pos, 1.0);
	vNormal = mat3(model) * nor;
})";

	const char* k_benchFS = R"(#version 330 core
in vec3 vNormal;
out vec4 fragColor;
void main()
{
	vec3 n = normalize(vNormal);
	float d = max(dot(n, normalize(vec3(0.5, 1.0, 0.3))), 0.0) * 0.8 + 0.2;
	fragColor = vec4(vec3(0.3, 0.6, 1.0) * d, 1.0);
})";

	GLuint compileBenchProgram(const char* vs, const char* fs)
	{
		auto compile = [](GLenum type, const char* src)
		{
			GLuint s = glCreateShader(type);
			glShaderSource(s, 1, &src, nullptr);
			glCompileShader(s);
			GLint ok = 0; glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
			if (!ok) { char log[1024]; glGetShaderInfoLog(s, 1024, nullptr, log); std::cout << "[BENCH] shader error: " << log << std::endl; }
			return s;
		};
		GLuint v = compile(GL_VERTEX_SHADER, vs), f = compile(GL_FRAGMENT_SHADER, fs);
		GLuint p = glCreateProgram();
		glAttachShader(p, v); glAttachShader(p, f); glLinkProgram(p);
		glDeleteShader(v); glDeleteShader(f);
		return p;
	}
}



void Viewer3D::onCreate()
{
	m_skyBox = Skybox();
	//resize maybe event based?
	winSize = getWindowSize();

	ObjectLoader OBJ;
	OBJ.LoadObjVertFromFile(OBJ.m_objFilePath, mesh.vertices, mesh.indices);
	GameObject* obj = new GameObject(0.0f, 0.0f, 20.0f, aspectRatio, m_camera, mesh);
	gameObjects.push_back(obj);

	ppFramebuffer = new FrameBuffer(winSize);

}


void Viewer3D::onUpdate(float deltaTime)
{
	winSize = getWindowSize();
	aspectRatio = winSize.x / winSize.y;

	
	handleInput(deltaTime);

	// [BENCH] instancing benchmark path replaces the normal scene to isolate the measurement
	if (benchMode != 0)
	{
		if (!benchInited) initBench();
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, static_cast<int>(winSize.x), static_cast<int>(winSize.y));
		glEnable(GL_DEPTH_TEST);
		glClearColor(0.05f, 0.05f, 0.08f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		drawBench(m_camera.getViewTransform(), m_camera.calcProjectionTransform(aspectRatio));
		return;
	}

	glEnable(GL_DEPTH_TEST);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ppFramebuffer->bind();

	RenderGameObjects(deltaTime);


	if (m_skyBox)
	{
		glDepthMask(GL_FALSE);
		m_skyBox->draw(m_camera);
		glDepthMask(GL_TRUE);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST);
	ppFramebuffer->bindShaderProg();

	glDrawArrays(GL_TRIANGLES, 0, 6);
}

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

	// [BENCH] toggle instancing benchmark: I = instanced (1 draw call), O = non-instanced (N draw calls), P = off
	if (getKey(GLFW_KEY_I)) benchMode = 1;
	if (getKey(GLFW_KEY_O)) benchMode = 2;
	if (getKey(GLFW_KEY_P)) benchMode = 0;

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
	_obj.model->m_modelTransform = glm::rotate(_obj.model->m_modelTransform, glm::radians(20 * _deltaTime), glm::vec3{ 0.0f,1.0f,0.0f });
	if (_obj.texture)
	{
		_obj.texture->bind(*_obj.shaderProgram, "cracksTexture", 0);
		_obj.texture2->bind(*_obj.shaderProgram, "normalTexture", 1);
	}
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(_obj.model->m_vertexBuffer.getIndexCount()), GL_UNSIGNED_INT, 0);

}

// [BENCH] build one shared cube VAO + an instance-matrix buffer for benchN cubes (lazy, on first use)
void Viewer3D::initBench()
{
	benchInited = true;
	Mesh cube = MeshData::getCube();
	benchIndexCount = static_cast<GLsizei>(cube.indices.size());

	glGenVertexArrays(1, &benchVAO);
	glBindVertexArray(benchVAO);

	glGenBuffers(1, &benchVBO);
	glBindBuffer(GL_ARRAY_BUFFER, benchVBO);
	glBufferData(GL_ARRAY_BUFFER, cube.vertices.size() * sizeof(Vertex), cube.vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &benchEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, benchEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, cube.indices.size() * sizeof(unsigned int), cube.indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, pos)));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, normal)));
	glEnableVertexAttribArray(2);

	// grid of model matrices
	const int side = static_cast<int>(std::ceil(std::cbrt(static_cast<double>(benchN))));
	benchMatrices.reserve(benchN);
	for (int i = 0; i < benchN; ++i)
	{
		const int x = i % side;
		const int y = (i / side) % side;
		const int z = i / (side * side);
		benchMatrices.push_back(glm::translate(glm::vec3((x - side / 2) * 2.0f, (y - side / 2) * 2.0f, (z - side / 2) * 2.0f)));
	}

	glGenBuffers(1, &benchInstVBO);
	glBindBuffer(GL_ARRAY_BUFFER, benchInstVBO);
	glBufferData(GL_ARRAY_BUFFER, benchMatrices.size() * sizeof(glm::mat4), benchMatrices.data(), GL_STATIC_DRAW);
	for (int i = 0; i < 4; ++i)
	{
		glEnableVertexAttribArray(6 + i);
		glVertexAttribPointer(6 + i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), reinterpret_cast<void*>(i * sizeof(glm::vec4)));
		glVertexAttribDivisor(6 + i, 1);
	}

	glBindVertexArray(0);

	benchProg = compileBenchProgram(k_benchVS, k_benchFS);
	benchLocView = glGetUniformLocation(benchProg, "viewTransformation");
	benchLocProj = glGetUniformLocation(benchProg, "projectionTransformation");
	benchLocModel = glGetUniformLocation(benchProg, "uModel");
	benchLocInstanced = glGetUniformLocation(benchProg, "uInstanced");

	std::cout << "[BENCH] initialized " << benchN << " cubes (side " << side << ")" << std::endl;
}

void Viewer3D::drawBench(const glm::mat4& view, const glm::mat4& proj)
{
	glUseProgram(benchProg);
	glUniformMatrix4fv(benchLocView, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(benchLocProj, 1, GL_FALSE, &proj[0][0]);
	glBindVertexArray(benchVAO);

	if (benchMode == 1)
	{
		// 1 draw call for all benchN cubes
		glUniform1i(benchLocInstanced, 1);
		glDrawElementsInstanced(GL_TRIANGLES, benchIndexCount, GL_UNSIGNED_INT, 0, benchN);
	}
	else
	{
		// benchN separate draw calls (the thing instancing replaces)
		glUniform1i(benchLocInstanced, 0);
		for (int i = 0; i < benchN; ++i)
		{
			glUniformMatrix4fv(benchLocModel, 1, GL_FALSE, &benchMatrices[i][0][0]);
			glDrawElements(GL_TRIANGLES, benchIndexCount, GL_UNSIGNED_INT, 0);
		}
	}
}


