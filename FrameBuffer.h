#pragma once
#include "UniqueResource.hpp"
#include "glad/glad.h"
#include "glm/glm.hpp"
#include <iostream>
#include "PostProcessingQuad.hpp"
#include "Shader.hpp"
#include "PixelShaderProgram.hpp"

class FrameBuffer
{
public:
	FrameBuffer(const glm::vec2& _winSize);
	void bind();
	int returnIndexCount();
	void bindShaderProg();

	PostProcessingQuad ppQuad{};
private:
	// fbo, rbo, fbt, dt
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



	static GLuint createVertexArrayObject();
	static void deleteVertexArrayObject(GLuint id);

	static GLuint createBuffer();
	static void deleteBuffer(GLuint id);

	UniqueResource m_vao{ createVertexArrayObject(), &deleteVertexArrayObject };
	UniqueResource m_vbo{ createBuffer(), &deleteBuffer }; 



	PixelShaderProgram pixelShader =
	{
		Shader{ "FB_VertexShader.glsl", GL_VERTEX_SHADER },
		Shader{ "FB_FragmentShader.glsl", GL_FRAGMENT_SHADER }
	};

	GLenum attachments[1] = { GL_COLOR_ATTACHMENT0 };

};

