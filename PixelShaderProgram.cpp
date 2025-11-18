#include "PixelShaderProgram.hpp"

PixelShaderProgram::PixelShaderProgram(const Shader& vertex, const Shader& fragment)
	: pixelShader{ glCreateProgram(), [](GLuint id) {glDeleteProgram(id);} }
{
	glAttachShader(*pixelShader, vertex.get());
	glAttachShader(*pixelShader, fragment.get());

	glLinkProgram(*pixelShader);

	glDetachShader(*pixelShader, vertex.get());
	glDetachShader(*pixelShader, fragment.get());

	texID = glGetUniformLocation(*pixelShader, "screenTexture");
}

void PixelShaderProgram::bind()
{
	glUseProgram(*pixelShader);
}
