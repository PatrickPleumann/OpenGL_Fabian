#include "GameObject.hpp"
#include "glm/gtx/transform.hpp"

GameObject::GameObject(float transformX, float transformY, float transformZ, Mesh _mesh)
{
	transform.Position.x = transformX;
	transform.Position.y = transformY;
	transform.Position.z = transformZ;

	model = Model
	{
		.m_vertexBuffer = VertexBuffer{_mesh.vertices, _mesh.indices},
		.m_modelTransform = glm::translate(glm::vec3{transformX,transformY,transformZ})
	};

	InitializeGameObject();
}

void GameObject::InitializeGameObject()
{
	model->m_vertexBuffer.bind();
}
