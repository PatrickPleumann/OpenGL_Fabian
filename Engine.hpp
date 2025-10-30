#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "Engine.hpp"

class Engine
{
public:
	bool init();
	void run();

protected:
	bool getKey(int key);
	glm::vec2 getMousePos();
	bool getMouseButton(int button);

	glm::vec2 getWindowSize();

private:
	virtual void onCreate() = 0;
	virtual void onUpdate(float deltaTime) = 0;

	GLFWwindow* window;
};


