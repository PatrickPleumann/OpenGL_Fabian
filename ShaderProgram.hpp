#pragma once
#include "UniqueResource.hpp"
#include "Shader.hpp"

class ShaderProgram
{
public:
	ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader);

private:
	UniqueResource m_id;
};

