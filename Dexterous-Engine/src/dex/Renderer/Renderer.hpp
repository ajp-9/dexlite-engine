#pragma once

#include <glm/vec4.hpp>
#include "../Scene/Scene.hpp"
#include "Shader/ShaderManager.hpp"
#include "ImGui/ImGuiAPI.hpp"

namespace dex
{
    class Renderer
    {
        Renderer(glm::uvec4 viewport);
        ~Renderer();

        void beginFrame();
        void endFrame();

        void update();
        void renderScene(Scene& scene);

        void setViewportSize(glm::uvec2 size);
        void setViewportPosition(glm::uvec2 position);

        void setClearColor(const glm::vec4& color);
        void clear();
    public:
        Shader::Manager shaderManager;
    private:
        /*// x, y = position of viewport
        // z, w = dimensions of viewport
        static glm::uvec4 s_LastViewport;*/

        ImGuiAPI m_ImGuiAPI;

        glm::uvec4 m_Viewport;

        friend class Engine;
        friend class Window;
    };
}
