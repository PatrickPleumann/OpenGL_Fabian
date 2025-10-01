#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Engine
{
public:
	bool init();
	void run();

private:
	virtual void onCreate() = 0;
	virtual void onUpdate() = 0;

	GLFWwindow* window;
};


