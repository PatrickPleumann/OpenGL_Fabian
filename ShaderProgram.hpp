#pragma once
#include "UniqueResource.hpp"

class Shader;

class ShaderProgram
{
public:
	ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader);
	//void use() const;

private:
	UniqueResource m_id;
};

