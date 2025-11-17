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

	std::vector<GameObject*> gameObjects; //contains all GO´s
	GLuint postProcessFBO;
	GLuint fbTexture;
	GLuint rbo;


};

