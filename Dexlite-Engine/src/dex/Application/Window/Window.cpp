#include "Window.hpp"

#include <glad/glad.h>
#include <iostream>
#include <imgui/imgui.h>

#include "../../Core/Engine.hpp"
#include "../../Renderer/Renderer.hpp"

#include "../Event/KeyEvent.hpp"

namespace dex
{
    Window::Window(glm::uvec2 windowDimensions)
    {
        if (!glfwInit())
            std::cout << "Error: Problem when initializing GLFW!\n";

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        //auto* vid = glfwGetVideoMode(glfwGetPrimaryMonitor());
        //m_Window_GLFW = glfwCreateWindow(vid->width, vid->height, "Dexlite Engine", glfwGetPrimaryMonitor(), NULL);

        m_Window_GLFW = glfwCreateWindow(windowDimensions.x, windowDimensions.y, "Dexlite Engine", NULL, NULL);

        if (!m_Window_GLFW)
        {
            glfwTerminate();
            std::cout << "Error: Problem when creating the GLFW window!\n";
        }

        glfwMakeContextCurrent(m_Window_GLFW);

        //glfwSetWindowUserPointer(m_Window_GLFW, this);

        glfwSwapInterval(1);

        /*
        ** Callbacks
        */

        glfwSetWindowSizeCallback(m_Window_GLFW, [](GLFWwindow* window, int width, int height)
            {
                if (width || height)
                    dex::Engine::renderer.setViewportSize(glm::uvec2(width, height));
            });

        glfwSetWindowPosCallback(m_Window_GLFW, [](GLFWwindow* window, int xpos, int ypos)
            {
                //dex::Engine::renderer.setViewportPosition(glm::uvec2(xpos, ypos));
            });


        /*glfwSetCharCallback(m_Window_GLFW, [](GLFWwindow* window, unsigned int ch)
            {
                std::cout << ch << "\n";
            });*/

        glfwSetKeyCallback(m_Window_GLFW, [](GLFWwindow* window, int key, int scancode, int action, int mods)
            {
                switch (action)
                {
                case GLFW_PRESS:
                {
                    Event::KeyEvent event = { Event::Type::KEY_PRESS, Event::Key(key) };
                    Engine::window.input.pushKeyEvent(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    Event::KeyEvent event = { Event::Type::KEY_RELEASE, Event::Key(key) };
                    Engine::window.input.pushKeyEvent(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    Event::KeyEvent event = { Event::Type::KEY_PRESS, Event::Key(key) };
                    Engine::window.input.pushKeyEvent(event);
                    break;
                }
                }
            });

        glfwSetCursorPosCallback(m_Window_GLFW, [](GLFWwindow* window, float64 xPos, float64 yPos)
            {
                static float32 lastX = xPos, lastY = yPos;

                Engine::window.input.pushMouseEvent(Event::MouseEvent(Event::Type::MOUSE, Event::MouseType::MOVE, glm::dvec2(xPos, yPos), glm::dvec2(-(lastX - xPos), lastY - yPos), Event::MouseButton::UNKNOWN, 0));

                lastX = xPos; lastY = yPos;
            });

        glfwSetMouseButtonCallback(m_Window_GLFW, [](GLFWwindow* window, int button, int action, int mods)
            {
                //std::cout << "Button: " << button << " Action: " << action << " Mods: " << mods << "\n";
                glm::dvec2 mousePos;
                glfwGetCursorPos(window, &mousePos.x, &mousePos.y);

                Event::MouseButton new_btn;
                switch (button)
                {
                case GLFW_MOUSE_BUTTON_1:
                    new_btn = Event::MouseButton::LEFT;
                    break;
                case GLFW_MOUSE_BUTTON_2:
                    new_btn = Event::MouseButton::RIGHT;
                    break;
                case GLFW_MOUSE_BUTTON_3:
                    new_btn = Event::MouseButton::MIDDLE;
                    break;
                default:
                    new_btn = Event::MouseButton::UNKNOWN;
                    break;
                }

                Event::MouseType mouseType;
                switch (action)
                {
                case GLFW_PRESS:
                    mouseType = Event::MouseType::BUTTON_PRESS;
                    break;
                case GLFW_RELEASE:
                    mouseType = Event::MouseType::BUTTON_RELEASE;
                    break;
                default:
                    mouseType = Event::MouseType::UNKNOWN;
                    break;
                }

                Engine::window.input.pushMouseEvent(Event::MouseEvent(Event::Type::MOUSE, mouseType, mousePos, glm::dvec2(0, 0), new_btn, 0));
            });

        glfwSetWindowCloseCallback(m_Window_GLFW, [](GLFWwindow* window)
            {
                dex::Engine::Stop();
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
        input.resetInput();


        glfwSwapBuffers(m_Window_GLFW);
        glfwPollEvents();
    }

    void Window::setWindowed()
    {
        if (!m_IsFullscreen)
        {
            m_WindowedDimensions = getDimensions();
            m_WindowedPosition = getPosition();
        }

        glfwSwapInterval(0);

        m_IsFullscreen = false;

        const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

        if (m_WindowedDimensions != glm::ivec2(0))
        {
            glfwSetWindowMonitor(m_Window_GLFW, NULL, m_WindowedPosition.x, m_WindowedPosition.y, m_WindowedDimensions.x, m_WindowedDimensions.y, mode->refreshRate);
        }
        else
        {
            glm::ivec2 current_dims = getDimensions();
            glfwSetWindowMonitor(m_Window_GLFW, NULL, m_WindowedPosition.x, m_WindowedPosition.y, current_dims.x, current_dims.y, mode->refreshRate);
        }

        glfwSwapInterval(1);
    }

    void Window::setFullscreen()
    {
        if (!m_IsFullscreen)
        {
            m_WindowedDimensions = getDimensions();
            m_WindowedPosition = getPosition();
        }

        glfwSwapInterval(0);

        m_IsFullscreen = true;

        auto* vid = glfwGetVideoMode(glfwGetPrimaryMonitor());
        const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

        glfwSetWindowMonitor(m_Window_GLFW, glfwGetPrimaryMonitor(), 0, 0, vid->width, vid->height, mode->refreshRate);

        glfwSwapInterval(1);
    }

    glm::ivec2 Window::getDimensions()
    {
        glm::ivec2 dimensions;
        glfwGetWindowSize(m_Window_GLFW, &dimensions.x, &dimensions.y);
        return dimensions;
    }

    glm::ivec2 Window::getPosition()
    {
        glm::ivec2 position;
        glfwGetWindowPos(m_Window_GLFW, &position.x, &position.y);
        return position;
    }

    void Window::setCaptureMouse(bool captured)
    {
        auto& io = ImGui::GetIO();
        m_IsMouseCaptured = captured;

        if (captured)
        {
            glfwSetInputMode(m_Window_GLFW, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            io.ConfigFlags |= ImGuiConfigFlags_NoMouse;
        }
        else
        {
            glfwSetInputMode(m_Window_GLFW, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            io.ConfigFlags &= ~ImGuiConfigFlags_NoMouse;
        }
    }
}
