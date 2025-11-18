#pragma once
#include "Shader.hpp"
#include "UniqueResource.hpp"

class PixelShaderProgram
{
public:
	PixelShaderProgram(const Shader& vertex, const Shader& fragment);
	void bind();

private:
	UniqueResource pixelShader;
	GLuint texID{};
};


