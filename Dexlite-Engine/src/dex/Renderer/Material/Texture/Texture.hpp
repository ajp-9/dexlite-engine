#pragma once

#include <vector>
#include <glad/glad.h>

#include <glm/vec2.hpp>
#include <tiny_gltf.h>

#include "../../../Util/Typedefs.hpp"

namespace dex
{
    // Can only be moved.
    class Texture
    {
    public:
        Texture() = default;

        Texture(const char* src, bool blending = true);
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

        ~Texture()
        {
            //DEX_LOG_ERROR("Deleted Texture ID: {}", m_ID);

            if (m_ID)
                glDeleteTextures(1, &m_ID);
        }

        inline bool isActive() { return m_ID; }

        inline void bind()
        {
            glActiveTexture(GL_TEXTURE0);
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
