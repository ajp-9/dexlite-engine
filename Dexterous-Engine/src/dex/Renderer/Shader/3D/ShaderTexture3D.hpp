#pragma once

#include "ShaderInterface3D.hpp"

namespace dex
{
    namespace Shader
    {
        class Texture3D : public Interface3D
        {
        public:
            Texture3D(const char* src = "assets/shaders/3d/texture.glsl", const char* name = "ShaderTexture3D")
                : Interface3D(src, name)
            {
                setSamplers();
            }

            void setSamplers()
            {
                setInt("u_TextureSampler", 0);
            }
        };
    }
}
