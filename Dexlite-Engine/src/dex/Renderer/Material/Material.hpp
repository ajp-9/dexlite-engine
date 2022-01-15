#pragma once

#include <memory>
#include "../Shader/ShaderBase.hpp"
#include "../Texture/Texture.hpp"

namespace dex
{
    namespace Material
    {
        // make base, + rm type

        enum class Type : uint8_t
        {
            NONE,
            BASE,
            DEFAULT_3D,
            ALBEDO_3D,
            TEXTURE_3D
        };
        
        template <class S> // Shader
        struct Base
        {
            Base(const std::shared_ptr<S>& shader)
                : m_Shader(shader)
            {}
        public:
            std::shared_ptr<S> m_Shader;
        };

    }
}
