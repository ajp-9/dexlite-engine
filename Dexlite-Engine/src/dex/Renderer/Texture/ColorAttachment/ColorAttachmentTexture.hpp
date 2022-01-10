#pragma once

#include <glad/glad.h>
#include <glm/vec2.hpp>

namespace dex
{
    class ColorAttachmentTexture
    {
    public:
        ColorAttachmentTexture(const glm::vec2& size)
            : m_Size(size)
        {
            create();
        }

        ~ColorAttachmentTexture() 
        { 
            if (m_ID) glDeleteTextures(1, &m_ID); 
        }

        ColorAttachmentTexture(const ColorAttachmentTexture& other) = delete;
        const ColorAttachmentTexture& operator=(const ColorAttachmentTexture& other) = delete;

        void resize(const glm::vec2& new_size)
        {
            m_Size = new_size;

            create();
        }

        void bind()
        {
            glBindTexture(GL_TEXTURE_2D, m_ID);
        }

        void unbind()
        {
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        GLuint getID() { return m_ID; }
        const glm::vec2& getSize() { return m_Size; }
    private:
        void create()
        {
            glGenTextures(1, &m_ID);
            bind();

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Size.x, m_Size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        }
    private:
        GLuint m_ID;
        glm::vec2 m_Size;
    };
}
