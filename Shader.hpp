#pragma once
#include <glad/glad.h>
#include <filesystem>
#include "UniqueResource.hpp"

class Shader
{
public:
	//holt sich den Shadercode aus dem Systempfad and speichert "GLuint"-ID innerhalb UniqueResource
	Shader(const std::filesystem::path& fileName, GLenum shaderType);
	GLuint get() const { return *m_id; }

private:
	UniqueResource m_id;
};

