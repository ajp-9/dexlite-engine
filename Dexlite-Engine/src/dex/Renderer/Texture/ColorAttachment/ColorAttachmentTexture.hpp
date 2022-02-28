#pragma once

#include <glad/gl.h>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

namespace dex
{
    enum class ColorAttachmentFormat
    {
        NONE,
        RED_INTEGER,
        RGB,
        RGBA,
    };

    class ColorAttachmentTexture
    {
    public:
        ColorAttachmentTexture(const glm::ivec2& size, GLenum internal_format, GLenum format)
            : m_Size(size), m_InternalFormat(internal_format), m_Format(format)
        {
            create();
        }

        ~ColorAttachmentTexture() 
        { 
            if (m_ID) glDeleteTextures(1, &m_ID); 
        }

        ColorAttachmentTexture(const ColorAttachmentTexture& other) = delete;
        const ColorAttachmentTexture& operator=(const ColorAttachmentTexture& other) = delete;


        ColorAttachmentTexture(ColorAttachmentTexture&& other) noexcept
            : m_InternalFormat(other.m_InternalFormat), m_Format(other.m_Format), m_Size(other.m_Size)
        {
            m_ID = other.m_ID;
            other.m_ID = 0;
        }
        ColorAttachmentTexture& operator=(ColorAttachmentTexture&& other) noexcept
        {
            if (this != &other)
            {
                m_ID = other.m_ID;
                other.m_ID = 0;
                
                m_InternalFormat = other.m_InternalFormat;
                m_Format = other.m_Format;
                m_Size = other.m_Size;
            }

            return *this;
        }

        void clear(const glm::vec4& color)
        {
            //unbind();

            //glDrawBuffer(GL_COLOR_ATTACHMENT0 + index);

            glClearColor(color.r, color.g, color.b, color.a);
            
            //glClear(GL_COLOR_BUFFER_BIT);

            //bind();
        }

        void resize(const glm::vec2& new_size)
        {
            m_Size = new_size;

            if (m_ID) glDeleteTextures(1, &m_ID);
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

        const GLuint getID() { return m_ID; }
        const glm::ivec2& getSize() { return m_Size; }
    private:
        void create()
        {
            glGenTextures(1, &m_ID);
            bind();

            glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, m_Size.x, m_Size.y, 0, m_Format, GL_UNSIGNED_BYTE, nullptr);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        }
    private:
        GLuint m_ID;

        GLenum m_InternalFormat;
        GLenum m_Format;

        glm::ivec2 m_Size;
    };
}
