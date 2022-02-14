#include "Window.hpp"

#include <glad/gl.h>
#include <iostream>
#include <imgui/imgui.h>

#include "../../Core/Engine.hpp"
#include "../../Renderer/Renderer.hpp"

#include "../Event/KeyEvent.hpp"

namespace dex
{
    Window::Window(const std::string& title, const glm::uvec2& dimensions)
        : m_Dimensions(dimensions)
    {
        if (!glfwInit())
        {
            DEX_LOG_CRITICAL("<dex::Window::Window()>: GLFW initialization was not successful.");
             
            return;
        }
        
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        //glfwWindowHint(GLFW_DECORATED, 0);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        //auto* vid = glfwGetVideoMode(glfwGetPrimaryMonitor());
        //Handle = glfwCreateWindow(vid->width, vid->height, "Dexlite Engine", glfwGetPrimaryMonitor(), NULL);

        Handle = glfwCreateWindow(dimensions.x, dimensions.y, title.c_str(), NULL, NULL);

        center();

        if (!Handle)
        {
            glfwTerminate();
            DEX_LOG_CRITICAL("<dex::Window::Window()>: Creating a GLFW window was not successful.");
        }

        glfwMakeContextCurrent(Handle);

        glfwSetWindowUserPointer(Handle, this);

        glfwSwapInterval(1);

        /*
        ** Callbacks
        */

        glfwSetWindowSizeCallback(Handle, [](GLFWwindow* window, int width, int height)
            {
                //if (width || height)
                //    dex::Engine::Renderer.setViewportSize(glm::uvec2(width, height));
            });

        glfwSetWindowPosCallback(Handle, [](GLFWwindow* window, int xpos, int ypos)
            {
                //dex::Engine::renderer.setViewportPosition(glm::uvec2(xpos, ypos));
            });


        /*glfwSetCharCallback(Handle, [](GLFWwindow* window, unsigned int ch)
            {
                std::cout << ch << "\n";
            });*/

        glfwSetKeyCallback(Handle, [](GLFWwindow* window, int key, int scancode, int action, int mods)
            {
                Window* this_window = (Window*)glfwGetWindowUserPointer(window);

                switch (action)
                {
                case GLFW_PRESS:
                {
                    Event::KeyEvent event = { Event::Type::KEY_PRESS, Event::Key(key) };
                    this_window->Input.pushKeyEvent(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    Event::KeyEvent event = { Event::Type::KEY_RELEASE, Event::Key(key) };
                    this_window->Input.pushKeyEvent(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    Event::KeyEvent event = { Event::Type::KEY_PRESS, Event::Key(key) };
                    this_window->Input.pushKeyEvent(event);
                    break;
                }
                }
            });

        glfwSetCursorPosCallback(Handle, [](GLFWwindow* window, float64 xPos, float64 yPos)
            {
                Window* this_window = (Window*)glfwGetWindowUserPointer(window);

                static float32 lastX = xPos, lastY = yPos;

                this_window->Input.pushMouseEvent(Event::MouseEvent(Event::Type::MOUSE, Event::MouseType::MOVE, glm::dvec2(xPos, yPos), glm::dvec2(-(lastX - xPos), lastY - yPos), Event::MouseButton::UNKNOWN, 0));

                lastX = xPos; lastY = yPos;
            });

        glfwSetMouseButtonCallback(Handle, [](GLFWwindow* window, int button, int action, int mods)
            {
                Window* this_window = (Window*)glfwGetWindowUserPointer(window);

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

                this_window->Input.pushMouseEvent(Event::MouseEvent(Event::Type::MOUSE, mouseType, mousePos, glm::dvec2(0, 0), new_btn, 0));
            });

        glfwSetWindowCloseCallback(Handle, [](GLFWwindow* window)
            {
                Window* this_window = (Window*)glfwGetWindowUserPointer(window);

                this_window->Open = false;
            });

        gladLoadGL(glfwGetProcAddress);

        //if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        //    DEX_LOG_CRITICAL("<dex::Window::Window()>: Window failed to initialize GLAD.");
        
        //int version =gladLoadGL(glfwGetProcAddress);

        //printf("GL %d.%d\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));


        Input.setWindowHandle(Handle);

        Open = true;
    }

    Window::~Window()
    {
        glfwDestroyWindow(Handle);
        glfwTerminate();
    }

    void Window::swapBuffers()
    {
        glfwSwapBuffers(Handle);
    }

    void Window::setTitle(const std::string& title)
    {
        glfwSetWindowTitle(Handle, title.c_str());
    }

    void Window::setSize(const glm::ivec2& size)
    {
        glfwSetWindowSize(Handle, size.x, size.y);
        m_Dimensions = size;
    }

    void Window::setWindowed()
    {
        if (!m_IsFullscreen)
        {
            m_Dimensions = getDimensions();
            m_Position = getPosition();
        }

        glfwSwapInterval(0);

        m_IsFullscreen = false;

        const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

        if (m_Dimensions != glm::ivec2(0))
        {
            glfwSetWindowMonitor(Handle, NULL, m_Position.x, m_Position.y, m_Dimensions.x, m_Dimensions.y, mode->refreshRate);
        }
        else
        {
            glm::ivec2 current_dims = getDimensions();
            glfwSetWindowMonitor(Handle, NULL, m_Position.x, m_Position.y, current_dims.x, current_dims.y, mode->refreshRate);
        }

        glfwSwapInterval(1);
    }

    void Window::setFullscreen()
    {
        if (!m_IsFullscreen)
        {
            m_Dimensions = getDimensions();
            m_Position = getPosition();
        }

        glfwSwapInterval(0);

        m_IsFullscreen = true;

        auto* vid = glfwGetVideoMode(glfwGetPrimaryMonitor());
        const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

        glfwSetWindowMonitor(Handle, glfwGetPrimaryMonitor(), 0, 0, vid->width, vid->height, mode->refreshRate);

        glfwSwapInterval(1);
    }

    void Window::center()
    {
        const auto* video_mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

        glfwSetWindowPos(Handle, (video_mode->width / 2) - (m_Dimensions.x / 2), (video_mode->height / 2) - (m_Dimensions.y / 2));
    }

    glm::ivec2 Window::getDimensions()
    {
        glm::ivec2 dimensions;
        glfwGetWindowSize(Handle, &dimensions.x, &dimensions.y);
        return dimensions;
    }

    glm::ivec2 Window::getPosition()
    {
        glm::ivec2 position;
        glfwGetWindowPos(Handle, &position.x, &position.y);
        return position;
    }

    void Window::setCaptureMouse(bool captured)
    {
        auto& io = ImGui::GetIO();
        m_IsMouseCaptured = captured;

        if (captured)
        {
            glfwSetInputMode(Handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            io.ConfigFlags |= ImGuiConfigFlags_NoMouse;
        }
        else
        {
            glfwSetInputMode(Handle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            io.ConfigFlags &= ~ImGuiConfigFlags_NoMouse;
        }
    }
}
