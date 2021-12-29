#pragma once

#include <glm/vec2.hpp>
#include <GLFW/glfw3.h>
#include <string>
#include <functional>

#include "../Event/EventBase.hpp"
#include "Input.hpp"

namespace dex
{
    namespace Layer { class Manager; }

    class Window
    {
        Window(glm::uvec2 windowDimensions);
        ~Window();

        // Update window when done handling events & rendering
        void update();
    public:
        void setWindowed();
        void setFullscreen();

        glm::ivec2 getDimensions();
        glm::ivec2 getPosition();

        void setCaptureMouse(bool captured);
        bool isMouseCaptured() { return m_IsMouseCaptured; };

        bool isFullscreen() { return m_IsFullscreen; }

        Input Input;
    private:
        GLFWwindow* m_Window_GLFW = nullptr;

        // Before fullscreen.
        glm::ivec2 m_WindowedDimensions = glm::ivec2(0);
        glm::ivec2 m_WindowedPosition = glm::ivec2(0);

        bool m_IsFullscreen = false;
        bool m_IsMouseCaptured = false;
    public:
        friend class Engine;
        friend class ImGuiAPI;
        friend class Layer::Manager;
        friend class Input;
    };
}
