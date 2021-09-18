#pragma once

#include "../../../Util/Typedefs.hpp"

namespace dex
{
    class Texture
    {
    public:
        Texture() {}
        Texture(const char* src, bool blending = true);
        ~Texture();

        bool isActive() { return m_ID; }

        void bind();
        void unbind();
    private:
        uint32 m_ID = 0;
    };
}
