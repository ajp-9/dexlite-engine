#pragma once

#include "../ShaderBase.hpp"

namespace dex
{
    namespace Shader
    {
        class Interface3D : public Base
        {
        public:
            Interface3D(const char* src = "assets/shaders/3d/texture.glsl", const char* name = "Shader3D");
            
            void setLocations3D();

            virtual void setProjectionViewMatrix(const glm::mat4& mat) override;
            virtual void setModelMatrix(const glm::mat4& mat) override;
        private:
            uint32 u_ProjectionViewMatrix_Location = 0;
            uint32 u_ModelMatrix_Location = 0;
        };
    }
}
