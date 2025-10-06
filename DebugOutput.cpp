#include "DebugOutput.hpp"
#include <glad/glad.h>
#include <iostream>

namespace
{
	void GLAPIENTRY
		MessageCallback(GLenum /* source*/,
			GLenum type,
			GLuint /*id*/,
			GLenum severity,
			GLsizei /*lenght*/,
			const GLchar* message,
			const void* /*userParam*/)
	{
		/* println somehow don´t works*/
		std::cout << ("GL CALLBACK : {} type = 0x{:x}, severity = 0x{:x}, message = {}",
			(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
			type, severity, message);
	}
}

void DebugOutput::enable()
{
	int flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
	{
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(MessageCallback, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	}
	else
	{
		std::cout <<("No GLFW_OPENGL_DEBUG_CONTEXT");
		/* println somehow don´t works*/
	}
}
