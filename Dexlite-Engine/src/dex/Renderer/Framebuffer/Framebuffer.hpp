#pragma once

#include <glad/glad.h>

#include "../Texture/ColorAttachment/ColorAttachmentTexture.hpp"
#include "RenderBuffer.hpp"

namespace dex
{
    class Framebuffer
    {
    public:
        Framebuffer(const glm::vec2& size);
        ~Framebuffer();

        Framebuffer(const Framebuffer& other) = delete;
        const Framebuffer& operator=(const Framebuffer& other) = delete;

        void resize(const glm::vec2& new_size);

        void bind();
        void unbind();

        GLuint getColorAttachmentTexture_ID() { return m_ColorAttachmentTexture.getID(); }

        GLuint getID() { return m_ID; }
        const glm::vec2& getSize() { return m_Size; }
    private:
        void create();
    private:
        GLuint m_ID;
        glm::vec2 m_Size;

        ColorAttachmentTexture m_ColorAttachmentTexture;
        RenderBuffer m_RenderBuffer;
    };   
}
