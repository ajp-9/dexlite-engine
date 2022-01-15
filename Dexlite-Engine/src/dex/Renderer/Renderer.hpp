#pragma once

#include <glm/vec4.hpp>

#include "../Scene/Scene.hpp"
#include "Shader/ShaderManager.hpp"
#include "Material/MaterialManager.hpp"
#include "ImGui/ImGuiAPI.hpp"

namespace dex
{   
    class Renderer
    {
    public:
        Renderer(GLFWwindow* window_handle);
        ~Renderer();

        void beginFrame();
        void endFrame();

        void update();

        void setViewportSize(glm::uvec2 size);
        //void setViewportPosition(glm::uvec2 position);

        void setClearColor(const glm::vec4& color);
        void clear();
    public:
        Shader::Manager ShaderManager;

        void enableDepthTest() { glEnable(GL_DEPTH_TEST); }
        void disableDepthTest() { glDisable(GL_DEPTH_TEST); }
    private:
        bool m_ChangeProjectionMatrixNext = true; // For when the window/viewport resizes

        ImGuiAPI m_ImGuiAPI;

        glm::uvec2 m_ScreenDimensions = glm::uvec2(0);
    public:
        friend class Window;
        friend class Scene;
    };
}
