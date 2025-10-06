#pragma once
#include "Engine.hpp"
#include "ShaderProgram.hpp"
#include "VertexBuffer.hpp"
#include <optional>
class Viewer3D : public Engine
{
	void onCreate() override;
	void onUpdate() override;

	std::optional<ShaderProgram> shaderProgram;

	std::optional<VertexBuffer> vertexBuffer;
};

