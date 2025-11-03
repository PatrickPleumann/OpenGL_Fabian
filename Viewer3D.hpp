#pragma once

#include "Engine.hpp"
#include "ShaderProgram.hpp"
#include <optional>
#include "Camera.hpp"
#include "Model.hpp"
#include "Texture.hpp"
#include "Skybox.hpp"

class Viewer3D : public Engine
{
	void onCreate() override;
	void onUpdate(float deltaTime) override;
	void handleInput(float deltaTime);

	std::optional<ShaderProgram> shaderProgram;

	std::optional<Model> m_triangle;
	std::optional<Model> m_quad;
	std::optional<Model> m_cube;
	
	std::optional<Texture> m_texture;

	Camera m_camera;

	std::optional<glm::vec2> m_lastMousePos;

	std::optional<Skybox> m_skyBox;
};

