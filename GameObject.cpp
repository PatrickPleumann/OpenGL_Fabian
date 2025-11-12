#include "GameObject.hpp"

GameObject::GameObject( float _posX, float _posY, float _posZ, float _aspectRatio, Camera _camera, Mesh _mesh)
{
	mesh = _mesh;

	transform.Position.x = _posX;
	transform.Position.y = _posY;
	transform.Position.z = _posZ;

	model = Model
	{
		.m_vertexBuffer = VertexBuffer{_mesh.vertices, _mesh.indices},
		.m_modelTransform = glm::translate(glm::vec3{_posX, _posY, _posZ})
	};

	shaderProgram = BloodWallShader{ vertexShader, fragmentShader };
}

GameObject::GameObject(float _posX,float _posY,float _posZ,float _aspectRatio, Camera _camera)
{
	transform.Position.x = _posX;
	transform.Position.y = _posY;
	transform.Position.z = _posZ;

	model = Model
	{
		.m_vertexBuffer = VertexBuffer{mesh->vertices, mesh->indices},
		.m_modelTransform = glm::translate(glm::vec3{_posX, _posY, _posZ})
	};

	shaderProgram = BloodWallShader{ vertexShader, fragmentShader };
}

GameObject::~GameObject() {}

