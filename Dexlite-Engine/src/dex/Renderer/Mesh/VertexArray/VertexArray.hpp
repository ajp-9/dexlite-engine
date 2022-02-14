#pragma once

#include <vector>
#include "Buffers/VertexBuffer.hpp"
#include "Buffers/IndexBuffer.hpp"

#include "../../../Util/Logging.hpp"

namespace dex
{
    class VertexArray
    {
    public:
        VertexArray() = default;

        void Create()
        {
            glGenVertexArrays(1, &m_ID);
            bind();

            m_VertexBuffers.Create();
            m_IndexBuffer.Create();
        }

        void Destroy()
        {
            m_IndexBuffer.Destroy();
            m_VertexBuffers.Destroy();

            if (m_ID) glDeleteVertexArrays(1, &m_ID);
        }

        VertexArray(const VertexArray& other) = delete;
        const VertexArray& operator=(const VertexArray& other) = delete;

        VertexArray(VertexArray&& other) noexcept
        {
            Destroy();

            m_ID = other.m_ID;
            m_VertexBuffers = std::move(other.m_VertexBuffers);
            m_IndexBuffer = std::move(other.m_IndexBuffer);

            other.m_ID = 0;
        }

        VertexArray& operator=(VertexArray&& other) noexcept
        {
            if (this != &other)
            {
                Destroy();
                
                m_ID = other.m_ID;
                m_VertexBuffers = std::move(other.m_VertexBuffers);
                m_IndexBuffer = std::move(other.m_IndexBuffer);

                other.m_ID = 0;
            }

            return *this;
        }

        void render()
        {
            bind();
            glDrawElements(GL_TRIANGLES, m_IndexBuffer.getCount(), GL_UNSIGNED_INT, 0);
        }

        void renderAsLines()
        {
            bind();
            glDrawElements(GL_LINES, m_IndexBuffer.getCount(), GL_UNSIGNED_INT, 0);
        }

        void bind()
        {
            glBindVertexArray(m_ID);
        }
        
        void unbind()
        {
            glBindVertexArray(0);
        }
    public:
        VertexBuffer m_VertexBuffers;
        IndexBuffer m_IndexBuffer;
    private:
        uint32 m_ID = 0;
    };
}
