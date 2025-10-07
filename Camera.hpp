#pragma once
#include "glm/glm.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/transform.hpp"
class Camera
{
public:
	glm::mat4 getViewTransform();

	glm::vec3 position{.0f,.0f, -5.0f};
	glm::vec3 direction{0.0f, 0.0f, 1.0f};
	glm::vec3 up{0.0f, 1.0f, 0.0f};

	glm::mat4 m_projectionTransform{ glm::perspective(glm::radians(60.0f),640.0f / 480.0f,0.1f,100.0f) };

};

