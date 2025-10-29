#pragma once
#include <optional>
#include "Model.hpp"
#include "ShaderProgram.hpp"
#include "Camera.hpp"

class Skybox
{
public:
	Skybox();
	void draw(const Camera& camera);

private:
	std::optional<Model> m_model;
	std::optional<ShaderProgram> m_shaderProgram; 
	UniqueResource m_texId
	{
		[] {GLuint id; glGenTextures(1,&id); return id;}(),
		[](GLuint id) {glDeleteTextures(1,&id); }
	};
};

