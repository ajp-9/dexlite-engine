#include "Framebuffer.hpp"

#include "../../Util/Logging.hpp"
#include "../../Core/Engine.hpp"

namespace dex
{
    Framebuffer::Framebuffer(const glm::vec2& size)
        : m_Size(size), m_ColorAttachmentTexture(size), m_RenderBuffer(size)
    {
        create();
    }

    Framebuffer::~Framebuffer()
    {
        if (m_ID) glDeleteFramebuffers(1, &m_ID);
    }

    void Framebuffer::resize(const glm::vec2& new_size)
    {
        m_ColorAttachmentTexture.resize(new_size);
        m_RenderBuffer.resize(new_size);
    }

    void Framebuffer::bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_ID);

        dex::Engine::Renderer.clear(); // Clear after binding the framebuffer.
    }

    void Framebuffer::unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void Framebuffer::create()
    {
        glGenFramebuffers(1, &m_ID);
        bind();

        m_ColorAttachmentTexture.bind();
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachmentTexture.getID(), 0);

        m_RenderBuffer.bind();
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RenderBuffer.getID());

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            DEX_LOG_ERROR("<dex::Framebuffer::create()>: Framebuffer not created successfully.");

        unbind();
        m_RenderBuffer.unbind();
        m_ColorAttachmentTexture.unbind();
    }
}
