#pragma once

#include <glad/gl.h>
#include <vector>

#include "../../Util/Typedefs.hpp"
#include "../Texture/ColorAttachment/ColorAttachmentTexture.hpp"
#include "RenderBuffer.hpp"

namespace dex
{
    class Framebuffer
    {
    public:
        Framebuffer(const glm::vec2& size, const std::vector<ColorAttachmentFormat>& formats);
        ~Framebuffer();

        Framebuffer(const Framebuffer& other) = delete;
        const Framebuffer& operator=(const Framebuffer& other) = delete;

        void resize(const glm::vec2& new_size);

        void bind();
        void unbind();

        // Framebuffer needs to be bound.
        void clearAttachment(uint32 index, const glm::vec4& color, bool depth = true);
        // Framebuffer needs to be bound.
        void clearAttachmentRed(uint32 index, int value);

        // Call after clearing attachments.
        // Framebuffer needs to be bound.
        void drawBuffers();

        GLuint getColorAttachmentTexture_ID(uint32 index = 0) { return m_ColorAttachments.at(index).getID(); }

        int readPixel(uint32 index, const glm::ivec2& location);

        const GLuint getID() { return m_ID; }
        const glm::vec2& getSize() { return m_Size; }
    private:
        void create();
    private:
        GLuint m_ID;
        glm::vec2 m_Size;

        //ColorAttachmentTexture m_ColorAttachmentTexture;
        std::vector<ColorAttachmentTexture> m_ColorAttachments;
        RenderBuffer m_RenderBuffer;
    };   
}
