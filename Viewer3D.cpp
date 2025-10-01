#include "Viewer3D.hpp"
#include "glad/glad.h"
#include "Shader.hpp"

void Viewer3D::onCreate()
{
	Shader vertexShader("VertexShader.glsl", GL_VERTEX_SHADER);
	Shader fragmentShader("FragmentShader.glsl", GL_FRAGMENT_SHADER);


}

void Viewer3D::onUpdate()
{
	glClear(GL_COLOR_BUFFER_BIT);
}
