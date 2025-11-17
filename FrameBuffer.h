#pragma once
#include "UniqueResource.hpp"
#include "glad/glad.h"
#include "glm/glm.hpp"
#include <iostream>

class FrameBuffer
{
public:
	FrameBuffer(const glm::vec2& _winSize);
	void bind();

private:
	GLuint createFramebufferObject();
	static void deleteFrameBuffers(GLuint _id);

	GLuint createRenderbufferObject();
	static void deleteRenderbufferObject(GLuint _id);
	
	GLuint createFramebufferTexture();
	static void deleteFramebufferTexture(GLuint _id);

	GLuint createDepthTexture();
	static void deleteDepthTexture(GLuint _id);

	UniqueResource m_fbo { createFramebufferObject(), &deleteFrameBuffers };
	UniqueResource m_rbo { createRenderbufferObject(), &deleteRenderbufferObject };
	UniqueResource m_fbt { createFramebufferTexture(), &deleteFramebufferTexture };
	UniqueResource m_dbt { createDepthTexture(), &deleteDepthTexture };
};

