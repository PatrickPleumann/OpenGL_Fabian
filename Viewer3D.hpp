#pragma once

#include "Engine.hpp"
#include "ShaderProgram.hpp"
#include <optional>
#include "Camera.hpp"
#include "Model.hpp"
#include "Texture.hpp"
#include "Skybox.hpp"
#include "GameObject.hpp"

class Viewer3D : public Engine
{
	void onCreate() override;
	void onUpdate(float deltaTime) override;
	void handleInput(float deltaTime);
	void InitializeGameObjects(GameObject& _obj, float _ascectRatio, float _deltaTime);
	void RenderGameObjects(float _deltaTime);
	std::optional<ShaderProgram> shaderProgram;

	Camera m_camera{};

	std::optional<Model> m_triangle;
	std::optional<Model> m_quad;
	std::optional<Model> m_cube;

	float aspectRatio;

	std::optional<GameObject> gameObj;
	
	std::optional<Texture> m_texture;


	std::optional<glm::vec2> m_lastMousePos;

	std::optional<Skybox> m_skyBox;

	std::vector<GameObject*> gameObjects;
};

