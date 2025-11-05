#pragma once
#include <vector>
#include "Component.hpp"
#include "glm/glm.hpp"
#include "Transform.hpp"
#include "Mesh.hpp"
#include "Model.hpp"
#include <optional>
#include "VertexBuffer.hpp"

class GameObject
{
public:

	GameObject(float transformX, float transformY, float transformZ, Mesh _mesh);


	Transform transform{};
private:


	void InitializeGameObject();
	
	std::optional<Model> model;
};

