#pragma once
#include "glm/glm.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/transform.hpp"
class Camera
{
public:
	glm::mat4 getViewTransform() const;
	glm::mat4 calcProjectionTransform(float aspectRatio);

	glm::vec3 getDirection() const;

	glm::mat4 projectionTransform{ glm::mat4{ glm::perspective(glm::radians(60.0f), 1920.0f / 1080.0f, 0.1f, 100.0f) }};

	glm::vec3 position { .0f,.0f, -5.0f };
	glm::vec3 up { 0.0f, 1.0f, 0.0f };
	glm::vec3 down { 0.0f,1.0f,0.0f };

	float yaw{ 0.0f };
	float pitch{ 0.0f };
};

