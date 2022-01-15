#pragma once

#include <GLFW/glfw3.h>

namespace dex
{
    class ImGuiAPI
    {
    public:
        ImGuiAPI(GLFWwindow* window_handle);
        ~ImGuiAPI();

        void beginFrame();
        void endFrame();
    };
}
