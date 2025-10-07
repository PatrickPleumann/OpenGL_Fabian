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
}

bool Engine::init()
{
	if (!glfwInit())
		return false;

#ifdef _DEBUG
	glfwWindowHint(GLFW_CONTEXT_DEBUG, GLFW_TRUE);
#endif

    window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return false;
    }

    glfwSetWindowPos(window, 1500, 500);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        return false;
    }
    std::cout << getInfoString();

#ifdef _DEBUG
    DebugOutput::enable();
#endif

    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
    onCreate();
    return true;
}

void Engine::run()
{
    double time{ 0.0 };
    while (!glfwWindowShouldClose(window))
    {
        auto now = glfwGetTime();
        double deltaTime = now - time;
        time = now;

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
