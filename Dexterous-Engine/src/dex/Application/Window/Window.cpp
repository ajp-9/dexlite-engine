#include "Window.hpp"

#include <glad/glad.h>

#include <iostream>

#include "../../Renderer/Renderer.hpp"

namespace dex
{
    Window::Window(glm::uvec2 windowDimensions)
    {
        if (!glfwInit())
            std::cout << "Error: Problem when initializing GLFW!\n";

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_Window_GLFW = glfwCreateWindow(windowDimensions.x, windowDimensions.y, "Dexterous Engine", NULL, NULL);
        if (!m_Window_GLFW)
        {
            glfwTerminate();
            std::cout << "Error: Problem when creating the GLFW window!\n";
        }

        glfwMakeContextCurrent(m_Window_GLFW);



        glfwSetWindowUserPointer(m_Window_GLFW, &m_Data);

        glfwSetWindowSizeCallback(m_Window_GLFW, [](GLFWwindow* window, int width, int height)
        {
            Renderer::setViewportSize(glm::uvec2(width, height));
        });

        glfwSetWindowPosCallback(m_Window_GLFW, [](GLFWwindow* window, int xpos, int ypos)
        {
            Renderer::setViewportPosition(glm::uvec2(xpos, ypos));
        });

        glfwSetKeyCallback(m_Window_GLFW, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            Data& data = *(Data*)glfwGetWindowUserPointer(window);

            //Event::KeyEvent event = Event::KeyEvent(key, scancode, action);
            //data.m_EventCallbackFunc()
        });

        // glad: load all OpenGL function pointers
        // ---------------------------------------
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Error: Window failed to initialize GLAD" << std::endl;
        }
    }

    Window::~Window()
    {
        glfwDestroyWindow(m_Window_GLFW);
        glfwTerminate();
    }

    void Window::update()
    {
        glfwSwapBuffers(m_Window_GLFW);
        glfwPollEvents();
    }

    glm::ivec2 Window::getDimensions()
    {
        glm::ivec2 dimensions;
        glfwGetWindowSize(m_Window_GLFW, &dimensions.x, &dimensions.y);
        return dimensions;
    }
}
