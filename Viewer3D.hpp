#pragma once

#include "Engine.hpp"
#include "ShaderProgram.hpp"
#include <optional>
#include "Camera.hpp"
#include "Model.hpp"
#include "Texture.hpp"
#include "Skybox.hpp"
#include "GameObject.hpp"
#include "FrameBuffer.h"

class Viewer3D : public Engine
{
private:
	void onCreate() override;
	void onUpdate(float deltaTime) override;
	void handleInput(float deltaTime);
	void InitializeGameObjects(GameObject& _obj, float _ascectRatio, float _deltaTime);
	void RenderGameObjects(float _deltaTime);

	Camera m_camera{};

	const float speed = { 10.0f };
	const float angularSpeed = { 20.0f };

	glm::vec2 winSize{};
	float aspectRatio{};

	std::optional<BloodWallShader> shaderProgram;
	std::optional<Texture> m_texture;
	std::optional<Skybox> m_skyBox;
	std::optional<glm::vec2> m_lastMousePos;
	FrameBuffer* ppFramebuffer;

	Mesh mesh{};

	std::vector<GameObject*> gameObjects; //contains all GO�s
	GLuint postProcessFBO;
	GLuint fbTexture;
	GLuint rbo;

	// [BENCH] self-contained instancing benchmark (raw GL). I=instanced, O=non-instanced, P=off
	void initBench();
	void drawBench(const glm::mat4& view, const glm::mat4& proj);
	int benchMode{ 0 }; // 0 = off (normal scene), 1 = instanced, 2 = non-instanced
	bool benchInited{ false };
	static const int benchN{ 50000 };
	GLuint benchVAO{}, benchVBO{}, benchEBO{}, benchInstVBO{}, benchProg{};
	GLsizei benchIndexCount{};
	GLint benchLocView{}, benchLocProj{}, benchLocModel{}, benchLocInstanced{};
	std::vector<glm::mat4> benchMatrices;

};

