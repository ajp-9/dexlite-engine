#pragma once

#include "../ShaderBase.hpp"

namespace dex
{
    namespace Shader
    {
        class Default3D : public Base
        {
        public:
            Default3D(const char* src = "assets/shaders/3d/default.glsl");

            void setLocations3D();

            void setProjectionViewMatrix(const glm::mat4& mat);
            void setModelMatrix(const glm::mat4& mat);

            void setTexTilingFactor(float tiling_factor);

            void setDiffuseMapEnabled(bool enabled);
            void setSpecularMapEnabled(bool enabled);
        private:
            uint32 m_ProjectionViewMatrix_Location = 0;
            uint32 m_ModelMatrix_Location = 0;

            uint32 m_TexTilingFactor_Location = 0;

            uint32 m_DiffuseMapSampler_Location = 0;
            uint32 m_DiffuseMapEnabled_Location = 0;

            uint32 m_SpecularMapSampler_Location = 0; 
            uint32 m_SpecularMapEnabled_Location = 0;
        };
    }
}
