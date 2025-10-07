#pragma once
#include "Engine.hpp"
#include "ShaderProgram.hpp"
#include "VertexBuffer.hpp"
#include <optional>
#include "Camera.hpp"
class Viewer3D : public Engine
{
	void onCreate() override;
	void onUpdate(float deltaTime) override;
	void handleInput(float deltaTime);

	std::optional<ShaderProgram> shaderProgram;
	std::optional<VertexBuffer> vertexBuffer;

	Camera m_camera;
};

