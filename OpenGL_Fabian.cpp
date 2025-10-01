#include "Engine.hpp"

#include <glad/glad.h> //comes before GLFW
#include <GLFW/glfw3.h>
#include <sstream>
#include <iostream>
#include "DebugOutput.hpp"
#include "glm/glm.hpp"


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return false;
    }

    glfwSetWindowPos(window, 1500,500);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        return -1;
    }

    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);

    onCreate();
    //TODO: create vertex data
    //TODO: create shader programm

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        onUpdate();
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        //TODO: draw triangle
        // bind vertex data
        // bind shader program
        // draw 

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
