#pragma once

#include <glad/glad.h>
#include <vector>

#include "../../../DataTypes/DataTypes.hpp"
#include "../../../../Util/Logging.hpp"

namespace dex
{
    enum class BufferDrawHint : uint32
    {
        STATIC = GL_STATIC_DRAW,
        DYNAMIC = GL_DYNAMIC_DRAW
    };

    class VertexBuffer
    {
    public:
        VertexBuffer()
        {
            glGenBuffers(1, &m_ID);
        }
        ~VertexBuffer()
        {
            //DEX_LOG_ERROR("Deleted VBO: {}", m_ID);

            if (m_ID)
                glDeleteBuffers(1, &m_ID);
        }

        VertexBuffer(const VertexBuffer& other) = delete;
        const VertexBuffer& operator=(const VertexBuffer& other) = delete;

        VertexBuffer(VertexBuffer&& other) noexcept
        {
            m_ID = other.m_ID;

            other.m_ID = 0;
        }
        VertexBuffer& operator=(VertexBuffer&& other) noexcept
        {
            if (this != &other)
            {
                m_ID = other.m_ID;

                other.m_ID = 0;
            }
            
            return *this;
        }

        template <typename V>
        void uploadData(const std::vector<V>& vertices, BufferDrawHint drawHint = BufferDrawHint::STATIC)
        {
            bind();
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(V), &vertices[0], uint32_t(drawHint));
        }
        
        void bind()
        {
            glBindBuffer(GL_ARRAY_BUFFER, m_ID);
        }
        void unbind()
        {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        template <typename V>
        void setVertexLayout(const std::vector<Data::Type>& types)
        {
            bind();

            uint64 currentOffset = 0;

            for (uint32 i = 0; i < types.size(); i++)
            {
                Data::Type d_type = types.at(i);

                uint32 d_gl_type = Data::getGLType(d_type);
                uint32 d_size = Data::getTypeSize(d_type);
                uint32 d_amount = Data::getTypeAmount(d_type);

                glEnableVertexAttribArray(i);

                if (d_type == Data::Type::BOOL ||
                    d_type == Data::Type::CHAR ||
                    d_type == Data::Type::DOUBLE ||
                    d_type == Data::Type::DVEC2 ||
                    d_type == Data::Type::DVEC3 ||
                    d_type == Data::Type::DVEC4 ||
                    d_type == Data::Type::INT ||
                    d_type == Data::Type::IVEC2 ||
                    d_type == Data::Type::IVEC3 ||
                    d_type == Data::Type::IVEC4 ||
                    d_type == Data::Type::UINT ||
                    d_type == Data::Type::UVEC2 ||
                    d_type == Data::Type::UVEC3 ||
                    d_type == Data::Type::UVEC4)
                {
                    glVertexAttribIPointer(i, d_amount, d_gl_type, sizeof(V), (const void*)currentOffset);
                }
                else
                {
                    glVertexAttribPointer(i, d_amount, d_gl_type, GL_FALSE, sizeof(V), (const void*)currentOffset);
                }

                currentOffset += d_size;
            }
        }
    private:
        uint32 m_ID = 0;
    };
}
