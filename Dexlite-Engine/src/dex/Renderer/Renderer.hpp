#pragma once

#include <glm/vec4.hpp>

#include "../Scene/Scene.hpp"
#include "../Application/Window/Window.hpp"
#include "Shader/ShaderManager.hpp"
#include "Material/MaterialManager.hpp"
#include "ImGui/ImGuiAPI.hpp"

namespace dex
{   
    class Renderer
    {
    public:
        Renderer(Window& window);
        ~Renderer();

        void beginFrame();
        void endFrame();

        void update();

        void setViewportSize(glm::uvec2 size);
        //void setViewportPosition(glm::uvec2 position);

        void setClearColor(const glm::vec4& color);
        void clear(const glm::vec4& color);
        void enableDepthTest() { glEnable(GL_DEPTH_TEST); }
        void disableDepthTest() { glDisable(GL_DEPTH_TEST); }
    public:
        Shader::Manager ShaderManager;
        ImGuiAPI m_ImGuiAPI;
    private:
        bool m_ChangeProjectionMatrixNext = true; // For when the window/viewport resizes
        glm::uvec2 m_ViewportSize = glm::uvec2(0);
    public:
        friend class Window;
        friend class Scene;
    };
}
