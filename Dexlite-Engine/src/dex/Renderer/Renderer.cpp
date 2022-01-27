#include "Renderer.hpp"

#include <glad/glad.h>

#include "../Util/Logging.hpp"

namespace dex
{
    Renderer::Renderer(Window& window)
        : m_ImGuiAPI(window.Handle)
    {
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Clear the color buffer

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        //glFrontFace(GL_CW);
        //glEnable(GL_CULL_FACE); // do w materials
        //glCullFace(GL_BACK);
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
        if (m_ViewportSize != size)
        {
            m_ViewportSize = size;
            m_ChangeProjectionMatrixNext = true;

            glViewport(0, 0, m_ViewportSize.x, m_ViewportSize.y);
        }
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
