#pragma once
#include <vector>
#include "Component.hpp"
#include "glm/glm.hpp"
#include "Transform.hpp"
#include "Mesh.hpp"
#include "Model.hpp"
#include <optional>
#include "VertexBuffer.hpp"
#include "Texture.hpp"
#include "Camera.hpp"
#include "GlobalShader.hpp"

class GameObject
{
private:

	Shader vertexShader = { "VertexShader.glsl", GL_VERTEX_SHADER };
	Shader fragmentShader = { "FragmentShader_Phong.glsl", GL_FRAGMENT_SHADER };

public:

	GameObject( float _posX, float _posY, float _posZ, float _aspectRatio,  Camera _camera, Mesh _mesh);
	GameObject( float _posX, float _posY, float _posZ, float _aspectRatio,  Camera _camera);
	~GameObject();

	Transform transform
	{
		.Position = {0.0f,0.0f,0.0f},
		.Rotation = {0.0f,0.0f,0.0f},
		.Scale = {1.0f, 1.0f, 1.0f}
	};

	std::optional<ShaderProgram> shaderProgram = ShaderProgram{ vertexShader, fragmentShader };

	std::optional<Texture> texture = Texture{ ".\\assets\\Treebark_Normal.jpg" };
	std::optional<Model> model;
};

