#pragma once

#include <vector>
#include <glad/gl.h>

#include <glm/vec2.hpp>
#include <tiny_gltf.h>

#include "../../Util/Typedefs.hpp"

namespace dex
{
    // Can only be moved.
    class Texture
    {
    public:
        Texture() = default;

        ~Texture() { if (m_ID) glDeleteTextures(1, &m_ID); }

        Texture(const std::string& src, bool blending = true);
        Texture(std::vector<uint8> image, const tinygltf::Sampler& sampler, glm::ivec2 dimensions, GLenum format, bool blending);

        Texture(const Texture& other) = delete;
        const Texture& operator=(const Texture& other) = delete;

        Texture(Texture&& other) noexcept
        {
            m_ID = other.m_ID;

            other.m_ID = 0;
        }
        Texture& operator=(Texture&& other) noexcept
        {
            if (this != &other)
            {
                m_ID = other.m_ID;

                other.m_ID = 0;
            }

            return *this;
        }

        inline bool isActive() { return m_ID; }

        inline void bind(uint32 tex_index = 0)
        {
            switch (tex_index)
            {
            case 0:
                glActiveTexture(GL_TEXTURE0);
                break;
            case 1:
                glActiveTexture(GL_TEXTURE1);
                break;
            case 2:
                glActiveTexture(GL_TEXTURE2);
                break;
            }
            
            glBindTexture(GL_TEXTURE_2D, m_ID);
        }

        inline void unbind()
        {
            glBindTexture(GL_TEXTURE_2D, 0);
        }
    private:
        uint32 m_ID = 0;
    };
}
