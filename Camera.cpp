#include "Camera.hpp"

glm::mat4 Camera::getViewTransform() const
{
	return glm::lookAt(position, position + getDirection(), up);
}

glm::mat4 Camera::calcProjectionTransform(float aspectRatio)
{
	projectionTransform = glm::mat4{ glm::perspective(glm::radians(60.0f), 1920.0f / 1080.0f, 0.1f, 100.0f) };
	return projectionTransform;
}

glm::vec3 Camera::getDirection() const
{
	auto rotationX = glm::rotate(glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f));
	auto rotationY = glm::rotate(glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f));

	auto dir = rotationY * rotationX * glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);

	return dir;
}
