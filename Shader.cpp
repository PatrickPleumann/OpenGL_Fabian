#include "Shader.hpp"
#include <fstream>
#include <iostream>

Shader::Shader(const std::filesystem::path& fileName, GLenum shaderType)
	:m_id{ glCreateShader(shaderType) , [](GLuint id) {glDeleteShader(id); } }
{
	std::ifstream file(fileName);
	std::stringstream s;
	s << file.rdbuf();
	std::string shaderCode = s.str();

	const char*  pShaderCode = shaderCode.c_str();
	glShaderSource(*m_id, 1, &pShaderCode, nullptr);

	glCompileShader(*m_id);

	GLint success = 0;
	glGetShaderiv(*m_id, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		int len;
		glGetShaderiv(*m_id, GL_INFO_LOG_LENGTH, &len);
		std::string errorString;
		errorString.resize(len);
		glGetShaderInfoLog(*m_id, len, nullptr, errorString.data());
		std::cout << "Error in Shader: " << errorString << std::endl;
		//std::prinln("Error in Shader: {}", errorString);
	}
}
