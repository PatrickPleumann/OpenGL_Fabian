#include "Camera.hpp"

glm::mat4 Camera::getViewTransform()
{
	return glm::lookAt(position, position + direction, up);
}
