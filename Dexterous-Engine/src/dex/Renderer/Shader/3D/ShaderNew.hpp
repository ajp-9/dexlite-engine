#pragma once

#include "../ShaderBase.hpp"

namespace dex
{
    namespace Shader
    {
        class New3D : public Base
        {
        public:
            New3D(const char* src = "assets/shaders/3d/new.glsl");

            void setLocations3D();

            virtual void setProjectionViewMatrix(const glm::mat4& mat);
            virtual void setModelMatrix(const glm::mat4& mat);
        private:
            uint32 u_ProjectionViewMatrix_Location = 0;
            uint32 u_ModelMatrix_Location = 0;
        };
    }
}
