#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Engine
{
public:
	bool init();
	void run();

protected:
	bool getKey(int key);

private:
	virtual void onCreate() = 0;
	virtual void onUpdate(float deltaTime) = 0;

	GLFWwindow* window;
};


