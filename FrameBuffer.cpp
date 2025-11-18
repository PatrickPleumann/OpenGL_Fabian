#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(const glm::vec2& _winSize)
{
	glBindFramebuffer(GL_FRAMEBUFFER, *m_fbo);

	glBindTexture(GL_TEXTURE_2D, *m_fbt);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _winSize.x, _winSize.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, *m_fbt, 0);

	glBindTexture(GL_TEXTURE_2D, *m_dbt);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, _winSize.x, _winSize.y, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindRenderbuffer(GL_RENDERBUFFER, *m_rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, _winSize.x, _winSize.y);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, *m_rbo);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		auto fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		std::cout << "Framebuffer Error: " << fboStatus << std::endl;
	}

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glNamedFramebufferDrawBuffers(*m_fbo, 1, attachments);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glBindVertexArray(*m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, *m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ppQuad.rectangleVertices), &ppQuad.rectangleVertices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1); 


}

void FrameBuffer::bind()
{

	glBindFramebuffer(GL_FRAMEBUFFER, *m_fbo);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	pixelShader.bind();
}

GLuint FrameBuffer::createFramebufferObject()
{
	GLuint id;
	glGenFramebuffers(1, &id);
	return id;
}

void FrameBuffer::deleteFrameBuffers(GLuint _id)
{
	glDeleteFramebuffers(1, &_id);
}

GLuint FrameBuffer::createRenderbufferObject()
{
	GLuint id;
	glGenRenderbuffers(1, &id);
	return id;
}

void FrameBuffer::deleteRenderbufferObject(GLuint _id)
{
	glDeleteRenderbuffers(1,&_id);
}

GLuint FrameBuffer::createFramebufferTexture()
{
	GLuint id;
	glGenTextures(1, &id);
	return id;
}

void FrameBuffer::deleteFramebufferTexture(GLuint _id)
{
	glDeleteTextures(1, &_id);
}

GLuint FrameBuffer::createDepthTexture()
{
	GLuint id;
	glGenTextures(1, &id);
	return id;
}

void FrameBuffer::deleteDepthTexture(GLuint _id)
{
	glDeleteTextures(1, &_id);
}

GLuint FrameBuffer::createVertexArrayObject()
{
	GLuint id;
	glGenVertexArrays(1, &id);
	return id;
}

void FrameBuffer::deleteVertexArrayObject(GLuint _id)
{
	glDeleteVertexArrays(1,&_id);
}

GLuint FrameBuffer::createBuffer()
{
	GLuint id;
	glGenBuffers(1, &id);
	return id;
}

void FrameBuffer::deleteBuffer(GLuint _id)
{
	glDeleteBuffers(1, &_id);
}
