#pragma once

#include <vector>
#include <glad/glad.h>

#include <glm/vec2.hpp>
#include <tiny_gltf.h>

#include "../../../Util/Typedefs.hpp"

namespace dex
{
    class Texture
    {
    public:
        Texture() {}
        Texture(const char* src, bool blending = true);
        Texture(std::vector<uint8> image, const tinygltf::Sampler& sampler, glm::ivec2 dimensions, GLenum format, bool blending);
        ~Texture();

        bool isActive() { return m_ID; }

        void bind();
        void unbind();
    private:
        uint32 m_ID = 0;
    };
}
