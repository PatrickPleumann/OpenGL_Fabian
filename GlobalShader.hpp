#pragma once
#include "Shader.hpp"
#include "ShaderProgram.hpp"
#include <optional>

class GlobalShader
{
private:
	//standard GlobalShader
	Shader vertexShader = { "VertexShader.glsl", GL_VERTEX_SHADER };
	Shader fragmentShader = { "FragmentShader_Phong.glsl", GL_FRAGMENT_SHADER };

public:
	std::optional<ShaderProgram> shaderProgram = ShaderProgram{ vertexShader,fragmentShader };
};
