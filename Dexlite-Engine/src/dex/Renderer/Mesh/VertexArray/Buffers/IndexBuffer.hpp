#pragma once

#include <vector>
#include <glad/glad.h>

#include "../../../../Util/Logging.hpp"
#include "../../../../Util/Typedefs.hpp"

namespace dex
{
    class IndexBuffer
    {
    public:
        IndexBuffer()
        {
            glGenBuffers(1, &m_ID);
        }

        ~IndexBuffer()
        {
            if (m_ID) glDeleteBuffers(1, &m_ID);
        }

        IndexBuffer(const IndexBuffer& other) = delete;
        const IndexBuffer& operator=(const IndexBuffer& other) = delete;

        IndexBuffer(IndexBuffer&& other) noexcept
            : m_ID(other.m_ID), m_Count(other.m_Count)
        {
            other.m_ID = 0;
        }
        IndexBuffer& operator=(IndexBuffer&& other) noexcept
        {
            if (this != &other)
            {
                m_ID = other.m_ID;
                m_Count = other.m_Count;

                other.m_ID = 0;
            }

            return *this;
        }

        void uploadData(const std::vector<uint32>& indices)
        {
            bind();
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
            m_Count = uint32(indices.size());
        }

        void bind()
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
        }

        void unbind()
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }

        uint32 getCount() const { return m_Count; }
    private:
        uint32 m_ID = 0;
        uint32 m_Count = 0;
    };
}
