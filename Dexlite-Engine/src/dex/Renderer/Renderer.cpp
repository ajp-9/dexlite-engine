#include "Renderer.hpp"

#include <glad/glad.h>

#include "../Util/Logging.hpp"

namespace dex
{
    Renderer::Renderer()
    {
        glEnable(GL_DEPTH_TEST);

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        //glFrontFace(GL_CW);
        //glEnable(GL_CULL_FACE); // do w materials
        //glCullFace(GL_BACK);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Clear the color buffer
    }

    Renderer::~Renderer()
    {
        
    }

    void Renderer::beginFrame()
    {
        m_ImGuiAPI.beginFrame();
    }

    void Renderer::endFrame()
    {
        m_ChangeProjectionMatrixNext = false;

        m_ImGuiAPI.endFrame();
    }

    void Renderer::update()
    {
    }

    void Renderer::setViewportSize(glm::uvec2 size)
    {
        m_ChangeProjectionMatrixNext = true;
        m_ScreenDimensions = size;

        glViewport(0, 0, m_ScreenDimensions.x, m_ScreenDimensions.y);
    }

    void Renderer::setClearColor(const glm::vec4& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void Renderer::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
}
