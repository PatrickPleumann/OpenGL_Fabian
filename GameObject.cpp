#include "GameObject.hpp"

GameObject::GameObject( float _posX, float _posY, float _posZ, float _aspectRatio, Camera _camera, Mesh _mesh)
{
	transform.Position.x = _posX;
	transform.Position.y = _posY;
	transform.Position.z = _posZ;

	model = Model
	{
		.m_vertexBuffer = VertexBuffer{_mesh.vertices, _mesh.indices},
		.m_modelTransform = glm::translate(glm::vec3{_posX, _posY, _posZ})
	};

	if (shaderProgram)
	{
		shaderProgram->use();
		shaderProgram->addCameraTransform(_camera.getViewTransform(), _camera.calcProjectionTransform(_aspectRatio), _camera.position);

		if (model)
		{
			model->m_vertexBuffer.bind();
			shaderProgram->setModelTransform(model->m_modelTransform);
			if (texture)
			{
				texture->bind(*shaderProgram, "baseColorTexture", 0);
			}
		}
	}

	InitializeGameObject();
}

GameObject::GameObject(float _posX,float _posY,float _posZ,float _aspectRatio, Camera _camera)
{
	Mesh mesh = MeshData::getCube();

	transform.Position.x = _posX;
	transform.Position.y = _posY;
	transform.Position.z = _posZ;

	model = Model
	{
		.m_vertexBuffer = VertexBuffer{mesh.vertices, mesh.indices},
		.m_modelTransform = glm::translate(glm::vec3{_posX, _posY, _posZ})
	};

	if (shaderProgram)
	{
		shaderProgram->use();
		shaderProgram->addCameraTransform(_camera.getViewTransform(), _camera.calcProjectionTransform(_aspectRatio), _camera.position);
		if (model)
		{
			model->m_vertexBuffer.bind();
			shaderProgram->setModelTransform(model->m_modelTransform);
			if (texture)
			{
				texture->bind(*shaderProgram, "baseColorTexture", 0);
			}
		}
	}

	InitializeGameObject();
}

GameObject::~GameObject() {}

void GameObject::InitializeGameObject()
{

}
