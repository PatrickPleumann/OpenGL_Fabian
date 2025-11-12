#pragma once

#include <vector>
#include "glm/glm.hpp"
#include "Transform.hpp"
#include "Mesh.hpp"
#include "Model.hpp"
#include <optional>
#include "VertexBuffer.hpp"
#include "Texture.hpp"
#include "Camera.hpp"
#include "GlobalShader.hpp"
#include "BloodWallShader.hpp"

class GameObject
{
private:
	Shader vertexShader = { "VertexShader.glsl", GL_VERTEX_SHADER };
	Shader fragmentShader = { "BloodWallShader.glsl", GL_FRAGMENT_SHADER };
	//Shader fragmentShader = { "FragmentShader_Phong.glsl", GL_FRAGMENT_SHADER };

public:

	GameObject(float _posX, float _posY, float _posZ, float _aspectRatio, Camera _camera, Mesh _mesh);
	GameObject(float _posX, float _posY, float _posZ, float _aspectRatio, Camera _camera);
	~GameObject();

	Transform transform
	{
		.Position = {0.0f,0.0f,0.0f},
		.Rotation = {0.0f,0.0f,0.0f},
		.Scale = {0.1f, 0.1f, 0.1f}
	};

	std::optional<BloodWallShader> shaderProgram;

	std::optional<Texture> texture = Texture{ ".\\assets\\Cracks.png" };
	std::optional<Texture> texture2 = Texture{ ".\\assets\\StoneWall.png" };

	std::optional<Model> model;
	std::optional<Mesh> mesh = MeshData::getCube();

};