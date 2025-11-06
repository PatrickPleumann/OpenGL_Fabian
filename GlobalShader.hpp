#pragma once
#include "Shader.hpp"
#include "ShaderProgram.hpp"
#include "Component.hpp"
#include <optional>

class GlobalShader : public Component
{
private:
	//standard GlobalShader
	Shader vertexShader = { "VertexShader.glsl", GL_VERTEX_SHADER };
	Shader fragmentShader = { "FragmentShader_Phong.glsl", GL_FRAGMENT_SHADER };

public:
	std::optional<ShaderProgram> shaderProgram = ShaderProgram{ vertexShader,fragmentShader };

	void InitializeComponent() override
	{
		shaderProgram->use();
	}
};
