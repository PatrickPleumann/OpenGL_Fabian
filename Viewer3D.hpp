#pragma once

#include "Engine.hpp"
#include "ShaderProgram.hpp"
#include <optional>
#include "Camera.hpp"
#include "Model.hpp"

class Viewer3D : public Engine
{
	void onCreate() override;
	void onUpdate(float deltaTime) override;
	void handleInput(float deltaTime);

	std::optional<ShaderProgram> shaderProgram;

	std::optional<Model> m_triangle;
	std::optional<Model> m_quad;
	std::optional<Model> m_cube;

	Camera m_camera;

	std::optional<glm::vec2> m_lastMousePos;
};

