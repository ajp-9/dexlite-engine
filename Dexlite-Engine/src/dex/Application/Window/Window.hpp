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
        Window();
        ~Window();

        // Update window when done handling events & rendering
        void update();
    public:
        void setTitle(const std::string& title);
        void setSize(const glm::ivec2& size);

        void setWindowed();
        void setFullscreen();

        void center();

        glm::ivec2 getDimensions();
        glm::ivec2 getPosition();

        void setCaptureMouse(bool captured);
        bool isMouseCaptured() { return m_IsMouseCaptured; };

        bool isFullscreen() { return m_IsFullscreen; }

        Input Input;
    private:
        GLFWwindow* m_Window_GLFW = nullptr;

        // Before fullscreen.
        glm::ivec2 m_Dimensions = glm::ivec2(0);
        glm::ivec2 m_Position = glm::ivec2(0);

        bool m_IsFullscreen = false;
        bool m_IsMouseCaptured = false;
    public:
        friend class Engine;
        friend class ImGuiAPI;
        friend class Layer::Manager;
        friend class Input;
    };
}
