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
    private:
        Renderer();
        ~Renderer();

        void beginFrame();
        void endFrame();

        void update();

        void setViewportSize(glm::uvec2 size);
        //void setViewportPosition(glm::uvec2 position);

        void setClearColor(const glm::vec4& color);
        void clear();
    public:
        void renderScene(Scene& scene);
    private:

    public:
        Shader::Manager shaderManager;
    private:
        bool m_ChangeProjectionMatrixNext = true; // For when the window/viewport resizes

        ImGuiAPI m_ImGuiAPI;

        glm::uvec2 m_ScreenDimensions = glm::uvec2(0);

        friend class Engine;
        friend class Window;
    };
}
