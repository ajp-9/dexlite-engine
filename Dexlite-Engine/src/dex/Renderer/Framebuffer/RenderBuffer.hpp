#pragma once

#include <glad/glad.h>

#include <glm/vec2.hpp>

namespace dex
{
    class RenderBuffer
    {
    public:
        RenderBuffer(const glm::vec2& size)
            : m_Size(size)
        {
            create();
        }

        ~RenderBuffer()
        {
            if (m_ID) glDeleteRenderbuffers(1, &m_ID);
        }

        RenderBuffer(const RenderBuffer& other) = delete;
        const RenderBuffer& operator=(const RenderBuffer& other) = delete;

        void resize(const glm::vec2& new_size)
        {
            m_Size = new_size;

            create();
        }

        void bind()
        {
            glBindRenderbuffer(GL_RENDERBUFFER, m_ID);
        }

        void unbind()
        {
            glBindRenderbuffer(GL_RENDERBUFFER, 0);
        }

        const GLuint getID() { return m_ID; }
        const glm::vec2& getSize() { return m_Size; }
    private:
        void create()
        {
            glGenRenderbuffers(1, &m_ID);
            bind();

            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Size.x, m_Size.y); // Use a single renderbuffer object for both a depth AND stencil buffer.
        }
    private:
        GLuint m_ID;
        glm::vec2 m_Size;
    };
}
