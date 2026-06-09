#include "Engine.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <sstream>
#include <iostream>
#include "DebugOutput.hpp"
namespace
{
	std::string getInfoString()
	{
		std::stringstream s;
		s << "Version: " << glGetString(GL_VERSION);
		return s.str();
	}

	void onSize( GLFWwindow*, int width, int height)
	{
		glViewport(0, 0, width, height);
	}
}

bool Engine::init()
{
	if (!glfwInit())
		return false;

#ifdef _DEBUG
	glfwWindowHint(GLFW_CONTEXT_DEBUG, GLFW_TRUE);
#endif

	window = glfwCreateWindow(1920, 1080, "Hello World", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return false;
	}
	glfwSetWindowPos(window, 200, 200);

	glfwSetWindowSizeCallback(window, onSize);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		glfwTerminate();
		return false;
	}

	glfwSwapInterval(0); // [BENCH] vsync off -> uncapped throughput measurement

	std::cout << getInfoString();

#ifdef _DEBUG
	DebugOutput::enable();
#endif

	glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
	glEnable(GL_CULL_FACE);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC1_ALPHA);   // with alpha channel

	glEnable(GL_DEPTH_TEST);

	onCreate();
	return true;
}

void Engine::run()
{
	double time{ 0.0 };
	double fpsTimer{ 0.0 };
	int frameCount{ 0 };
	while (!glfwWindowShouldClose(window))
	{
		auto now = glfwGetTime();
		double deltaTime = now - time;
		time = now;

		// [BENCH] rolling 1s FPS / frame-time report
		++frameCount;
		fpsTimer += deltaTime;
		if (fpsTimer >= 1.0)
		{
			std::cout << "[BENCH] FPS: " << frameCount << " | "
				<< (1000.0 * fpsTimer / frameCount) << " ms/frame" << std::endl;
			frameCount = 0;
			fpsTimer = 0.0;
		}

		onUpdate(deltaTime);
		


		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();
}

bool Engine::getKey(int key)
{
	if (!window)
	{
		return false;
	}
	return glfwGetKey(window, key) == GLFW_PRESS;

}

glm::vec2 Engine::getMousePos()
{
	if (!window)
	{
		return{};
	}
	double xPos;
	double yPos;

	glfwGetCursorPos(window, &xPos, &yPos);

	return glm::vec2(xPos, yPos);
}

bool Engine::getMouseButton(int button)
{
	if (window)
	{
		return glfwGetMouseButton(window, button);
	}
	return false;
}

glm::vec2 Engine::getWindowSize()
{
	if (!window)
	{
		return { 640.0f, 480.0f };
	}

	int width{};
	int height{};
	glfwGetWindowSize(window, &width, &height);
	return glm::vec2(static_cast<float>(width),static_cast<float>(height));
}
