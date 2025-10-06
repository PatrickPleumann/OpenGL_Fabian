#include "Viewer3D.hpp"
#include "glad/glad.h"
#include "Shader.hpp"
#include  <vector>
#include "Vertex.hpp"

void Viewer3D::onCreate()
{
	std::vector<Vertex> vertices
	{
		Vertex{.pos = {-0.5f, -0.5f, 0.0f},.color = {1.0f,0.0f,0.0f,1.0f}},
		Vertex{.pos = {0.5f, -0.5f, 0.0f},.color = {0.0f,1.0f,0.0f,1.0f}},
		Vertex{.pos = {0.0f, 0.5f, 0.0f},.color = {0.0f,0.0f,1.0f,1.0f}}
	};
	vertexBuffer = VertexBuffer{ vertices };
	Shader vertexShader("VertexShader.glsl", GL_VERTEX_SHADER);
	Shader fragmentShader("FragmentShader.glsl", GL_FRAGMENT_SHADER);
	shaderProgram = ShaderProgram(vertexShader, fragmentShader);

}

void Viewer3D::onUpdate()
{
	glClear(GL_COLOR_BUFFER_BIT);

	if (shaderProgram)
	{
		vertexBuffer->bind();

		shaderProgram->use();

		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
}
