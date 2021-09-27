#pragma once

#include <vector>
#include <glm/vec2.hpp>

#include "../../../Util/Typedefs.hpp"

namespace dex
{
    class Texture
    {
    public:
        Texture() {}
        Texture(std::vector<uint8> image, glm::ivec2 dimensions, int channels, bool blending);
        Texture(const char* src, bool blending = true);
        ~Texture();

        bool isActive() { return m_ID; }

        void bind();
        void unbind();
    private:
        uint32 m_ID = 0;
    };
}
