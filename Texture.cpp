#define STB_IMAGE_IMPLEMENTATION
#include "Texture.hpp"
#include <stb_image.h> // only because of #define STB_IMAGE_IMPLEMENTATION before including <stb_image.h>
#include "ShaderProgram.hpp"
#include "Image.hpp"
#include "BloodWallShader.hpp"


Texture::Texture(const std::string& path)
{

	Image image(path);

	if (image.buffer)
	{
		glBindTexture(GL_TEXTURE_2D, *m_id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image.width, image.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.buffer);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	
}
void Texture::bind(const BloodWallShader& shader, const std::string& uniformName, int textureUnit)
{
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_2D, *m_id);

	shader.use();
	auto textureUniform = glGetUniformLocation(shader.get(), uniformName.c_str());
	glUniform1i(textureUniform, textureUnit );
}