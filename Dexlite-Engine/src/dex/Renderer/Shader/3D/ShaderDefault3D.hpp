#pragma once

#include "../ShaderBase.hpp"
#include <glad/glad.h>

namespace dex
{
    namespace Shader
    {
        class Default3D : public Base
        {
        public:
            Default3D(const std::string& src = "assets/shaders/3d/default.glsl")
                : Base(src, "dex::Shader::Default3D", Type::DEFAULT_3D)
            {
                bind();

                setLocations3D();

                m_AmbientLight_Enabled_Location = glGetUniformLocation(m_ProgramID, "u_AmbientLight.Enabled");
                m_AmbientLight_Color_Location = glGetUniformLocation(m_ProgramID, "u_AmbientLight.Color");

                m_DirectionalLight_Enabled_Location = glGetUniformLocation(m_ProgramID, "u_DirectionalLight.Enabled");
                m_DirectionalLight_Color_Location = glGetUniformLocation(m_ProgramID, "u_DirectionalLight.Color");
                m_DirectionalLight_Direction_Location = glGetUniformLocation(m_ProgramID, "u_DirectionalLight.Direction");

                m_TexTilingFactor_Location = glGetUniformLocation(m_ProgramID, "u_TexTilingFactor");

                m_DiffuseMapSampler_Location = glGetUniformLocation(m_ProgramID, "u_DiffuseMapSampler");
                m_DiffuseMapEnabled_Location = glGetUniformLocation(m_ProgramID, "u_DiffuseMapEnabled");

                m_SpecularMapSampler_Location = glGetUniformLocation(m_ProgramID, "u_SpecularMapSampler");
                m_SpecularMapEnabled_Location = glGetUniformLocation(m_ProgramID, "u_SpecularMapEnabled");

                glUniform1i(m_DiffuseMapSampler_Location, 0); // for GL_TEXTURE_0,1,2,3,4
                glUniform1i(m_SpecularMapSampler_Location, 1);
            }

            void setLocations3D()
            {
                m_ProjectionViewMatrix_Location = glGetUniformLocation(m_ProgramID, "u_ProjectionViewMatrix");
                m_ModelMatrix_Location = glGetUniformLocation(m_ProgramID, "u_ModelMatrix");
            }

            virtual void updateGlobalUniforms(const GlobalUniforms& global_uniforms) override
            {
                if (global_uniforms.isProjectionViewMatrixDirty())
                    setProjectionViewMatrix(global_uniforms.getProjectionViewMatrix());

                if (global_uniforms.isAmbientLightDirty())
                {
                    setAmbientLight_Enabled(global_uniforms.getAmbientLight().Enabled);
                    setAmbientLight_Color(global_uniforms.getAmbientLight().Color);
                }

                if (global_uniforms.isDirectionalLightDirty())
                {
                    setDirectionalLight_Enabled(global_uniforms.getDirectionalLight().Enabled);
                    setDirectionalLight_Color(global_uniforms.getDirectionalLight().Color);
                    setDirectionalLight_Direction(global_uniforms.getDirectionalLight().Direction);
                }
            }

            inline void setProjectionViewMatrix(const glm::mat4& mat) 
            {
                glUniformMatrix4fv(m_ProjectionViewMatrix_Location, 1, GL_FALSE, glm::value_ptr(mat));
            }

            inline void setModelMatrix(const glm::mat4& mat) 
            {
                glUniformMatrix4fv(m_ModelMatrix_Location, 1, GL_FALSE, glm::value_ptr(mat));
            }

            // Ambient Light:

            inline void setAmbientLight_Enabled(bool enabled)
            {
                glUniform1i(m_AmbientLight_Enabled_Location, enabled);
            }

            inline void setAmbientLight_Color(const glm::vec3& color)
            {
                glUniform3f(m_AmbientLight_Color_Location, color.x, color.y, color.z);
            }

            // Directional Light:

            inline void setDirectionalLight_Enabled(bool enabled)
            {
                glUniform1i(m_DirectionalLight_Enabled_Location, enabled);
            }

            inline void setDirectionalLight_Color(const glm::vec3& color)
            {
                glUniform3f(m_DirectionalLight_Color_Location, color.x, color.y, color.z);
            }

            inline void setDirectionalLight_Direction(const glm::vec3& dir)
            {
                glUniform3f(m_DirectionalLight_Direction_Location, dir.x, dir.y, dir.z);
            }

            // Texture Uniforms:

            inline void setTexTilingFactor(float tiling_factor)
            { 
                glUniform1f(m_TexTilingFactor_Location, tiling_factor); 
            }

            inline void setDiffuseMap_Enabled(bool enabled)
            {
                glUniform1i(m_DiffuseMapEnabled_Location, enabled);
            }

            inline void setSpecularMapEnabled(bool enabled)
            {
                glUniform1i(m_SpecularMapEnabled_Location, enabled); 
            }
        private:
            uint32 m_ProjectionViewMatrix_Location = 0;
            uint32 m_ModelMatrix_Location = 0;

            uint32 m_AmbientLight_Enabled_Location = 0;
            uint32 m_AmbientLight_Color_Location = 0;

            uint32 m_DirectionalLight_Enabled_Location = 0;
            uint32 m_DirectionalLight_Color_Location = 0;
            uint32 m_DirectionalLight_Direction_Location = 0;

            uint32 m_TexTilingFactor_Location = 0;

            uint32 m_DiffuseMapSampler_Location = 0;
            uint32 m_DiffuseMapEnabled_Location = 0;

            uint32 m_SpecularMapSampler_Location = 0;
            uint32 m_SpecularMapEnabled_Location = 0;
        };
    }
}
