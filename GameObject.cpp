#include "GameObject.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/transform.hpp"



GameObject::GameObject(float transformX, float transformY, float transformZ)
{
	Mesh mesh = MeshData::getCube();
	
	transform.Position.x = transformX;
	transform.Position.y = transformY;
	transform.Position.z = transformZ;

	model = Model
	{
		.m_vertexBuffer = VertexBuffer{mesh.vertices, mesh.indices},
		.m_modelTransform = glm::translate(glm::vec3{transformX,transformY,transformZ})
	};
}



GameObject::GameObject(float transformX, float transformY, float transformZ, Mesh _mesh)
	: GameObject(transformX, transformY, transformZ)
{
	model = Model
	{
		.m_vertexBuffer = VertexBuffer{_mesh.vertices, _mesh.indices},
		.m_modelTransform = glm::translate(glm::vec3{transformX,transformY,transformZ})
	};
}

GameObject::~GameObject() {}

void GameObject::InitializeGameObject()
{
	model->m_vertexBuffer.InitializeComponent();
	shader.InitializeComponent();
}
