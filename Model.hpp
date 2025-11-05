#pragma once
#include "Component.hpp"
#include "VertexBuffer.hpp"

struct Model
{
	VertexBuffer m_vertexBuffer;
	glm::mat4 m_modelTransform;

};

