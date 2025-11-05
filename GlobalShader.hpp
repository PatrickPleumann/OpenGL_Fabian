#pragma once
#include "Shader.hpp"
#include "ShaderProgram.hpp"
#include "Component.hpp"

class GlobalShader : public Component
{
public:
	void InitializeComponent() override
	{
		shaderProgram.use();
	}
private:
	//standard GlobalShader
	Shader vertexShader = { "VertexShader.glsl", GL_VERTEX_SHADER };
	Shader fragmentShader = { "FragmentShader_Phong.glsl", GL_FRAGMENT_SHADER };
	ShaderProgram shaderProgram = { vertexShader,fragmentShader };
};
