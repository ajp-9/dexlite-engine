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

                // Material:

                m_TexTilingFactor_Location = glGetUniformLocation(m_ProgramID, "u_Material.TexTilingFactor");

                m_BaseColorTextureEnabled_Location = glGetUniformLocation(m_ProgramID, "u_Material.BaseColorTextureEnabled");
                m_BaseColorTextureSampler_Location = glGetUniformLocation(m_ProgramID, "u_Material.BaseColorTextureSampler");

                m_RoughnessTextureEnabled_Location = glGetUniformLocation(m_ProgramID, "u_Material.RoughnessTextureEnabled");
                m_RoughnessTextureSampler_Location = glGetUniformLocation(m_ProgramID, "u_Material.RoughnessTextureSampler");

                m_EmissiveTextureEnabled_Location = glGetUniformLocation(m_ProgramID, "u_Material.EmissiveTextureEnabled");
                m_EmissiveTextureSampler_Location = glGetUniformLocation(m_ProgramID, "u_Material.EmissiveTextureSampler");

                glUniform1i(m_BaseColorTextureEnabled_Location, 0); // for GL_TEXTURE0
                glUniform1i(m_RoughnessTextureSampler_Location, 1); // for GL_TEXTURE1
                glUniform1i(m_EmissiveTextureSampler_Location, 2); // for GL_TEXTURE2

                // Light:

                m_AmbientLight_Enabled_Location = glGetUniformLocation(m_ProgramID, "u_AmbientLight.Enabled");
                m_AmbientLight_Color_Location = glGetUniformLocation(m_ProgramID, "u_AmbientLight.Color");

                m_DirectionalLight_Enabled_Location = glGetUniformLocation(m_ProgramID, "u_DirectionalLight.Enabled");
                m_DirectionalLight_Color_Location = glGetUniformLocation(m_ProgramID, "u_DirectionalLight.Color");
                m_DirectionalLight_Direction_Location = glGetUniformLocation(m_ProgramID, "u_DirectionalLight.Direction");
            }

            void setLocations3D()
            {
                m_CameraPosition_Location = glGetUniformLocation(m_ProgramID, "u_CameraPosition");

                m_ProjectionViewMatrix_Location = glGetUniformLocation(m_ProgramID, "u_ProjectionViewMatrix");
                m_ModelMatrix_Location = glGetUniformLocation(m_ProgramID, "u_ModelMatrix");
                m_InverseModelMatrix_Location = glGetUniformLocation(m_ProgramID, "u_InverseModelMatrix");
            }

            virtual void updateGlobalUniforms(const GlobalUniforms& global_uniforms) override
            {
                if (global_uniforms.isCameraPositionDirty())
                    setCameraPosition(global_uniforms.getCameraPosition());

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

            inline void setCameraPosition(const glm::vec3& cam_pos)
            {
                glUniform3f(m_CameraPosition_Location, cam_pos.x, cam_pos.y, cam_pos.z);
            }

            inline void setProjectionViewMatrix(const glm::mat4& mat) 
            {
                glUniformMatrix4fv(m_ProjectionViewMatrix_Location, 1, GL_FALSE, glm::value_ptr(mat));
            }

            inline void setModelMatrix(const glm::mat4& mat) 
            {
                glUniformMatrix4fv(m_ModelMatrix_Location, 1, GL_FALSE, glm::value_ptr(mat));

                glm::mat3 inverse_mat = glm::transpose(glm::inverse(mat));
                glUniformMatrix3fv(m_InverseModelMatrix_Location, 1, GL_FALSE, glm::value_ptr(inverse_mat));
            }

            // Texture Uniforms:

            inline void setTexTilingFactor(float tiling_factor)
            {
                glUniform1f(m_TexTilingFactor_Location, tiling_factor);
            }

            inline void setBaseColorTexture_Enabled(bool enabled)
            {
                glUniform1i(m_BaseColorTextureEnabled_Location, enabled);
            }

            inline void setRoughnessTextureEnabled(bool enabled)
            {
                glUniform1i(m_RoughnessTextureEnabled_Location, enabled);
            }

            inline void setEmissiveTextureEnabled(bool enabled)
            {
                glUniform1i(m_EmissiveTextureEnabled_Location, enabled);
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
        private:
            uint32 m_CameraPosition_Location = 0;

            uint32 m_ProjectionViewMatrix_Location = 0;
            uint32 m_ModelMatrix_Location = 0;
            uint32 m_InverseModelMatrix_Location = 0;

            uint32 m_BaseColorTextureEnabled_Location = 0;
            uint32 m_BaseColorTextureSampler_Location = 0;

            uint32 m_RoughnessTextureEnabled_Location = 0;
            uint32 m_RoughnessTextureSampler_Location = 0;

            uint32 m_EmissiveTextureEnabled_Location = 0;
            uint32 m_EmissiveTextureSampler_Location = 0;

            uint32 m_AmbientLight_Enabled_Location = 0;
            uint32 m_AmbientLight_Color_Location = 0;

            uint32 m_DirectionalLight_Enabled_Location = 0;
            uint32 m_DirectionalLight_Color_Location = 0;
            uint32 m_DirectionalLight_Direction_Location = 0;

            uint32 m_TexTilingFactor_Location = 0;
        };
    }
}
