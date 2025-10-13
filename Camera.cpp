#include "Camera.hpp"

glm::mat4 Camera::getViewTransform()
{
	return glm::lookAt(position, position + getDirection(), up);
}

glm::mat4 Camera::getProjectionTransform(float aspectRatio)
{
	return glm::mat4{ glm::perspective(glm::radians(60.0f), 640.0f / 480.0f, 0.1f, 100.0f) };
}

glm::vec3 Camera::getDirection()
{
	auto rotationX = glm::rotate(glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f));
	auto rotationY = glm::rotate(glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f));

	auto dir = rotationY * rotationX * glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);

	return dir;
}
