#pragma once
#include <string>
#include "UniqueResource.hpp"


class BloodWallShader;

class Texture
{
public:
	Texture(const std::string& path);
	void bind(const BloodWallShader& shader, const std::string& uniformName, const int textureUnit);

private:
	UniqueResource m_id
	{
		[] {GLuint id; glGenTextures(1,&id); return id; }(),
		[] (GLuint id) { glDeleteTextures(1,&id); }
	};
};

