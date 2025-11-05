#pragma once
#include <vector>
#include "Component.hpp"
#include "glm/glm.hpp"
#include "Transform.hpp"
#include "Mesh.hpp"
#include "Model.hpp"
#include <optional>
#include "VertexBuffer.hpp"
#include "GlobalShader.hpp"

class GameObject
{
public:

	GameObject(float transformX, float transformY, float transformZ);
	GameObject(float transformX, float transformY, float transformZ, Mesh _mesh);
	~GameObject();

	void InitializeGameObject();

	Transform transform{};
private:

	
	std::optional<Model> model;
	GlobalShader shader;
};

