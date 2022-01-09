#pragma once

#include "../ShaderBase.hpp"
#include <glad/glad.h>
#include "../../../Util/Logging.hpp"

namespace dex
{
    namespace Shader
    {
        struct PointLight_Locations
        {
            GLuint Enabled;
            GLuint Color;
            GLuint Position;

            GLuint Constant;
            GLuint Linear;
            GLuint Quadratic;
        };

        class Default3D : public Base
        {
        public:
            Default3D(const std::string& src = "assets/shaders/3d/default.glsl");

            void setLocations3D();

            virtual void updateGlobalUniforms(const GlobalUniforms& global_uniforms) override;

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

            // rollup into a struct later

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

            // Point Lights:

            inline void setPointLights(const std::vector<Light::Point>& lights)
            {
                if (m_PointLights_Locations.size() >= lights.size())
                {
                    for (uint32 i = 0; i < lights.size(); i++)
                    {
                        glUniform1i(m_PointLights_Locations.at(i).Enabled, lights.at(i).Enabled);
                        glUniform3f(m_PointLights_Locations.at(i).Color, lights.at(i).Color.x, lights.at(i).Color.y, lights.at(i).Color.z);
                        glUniform3f(m_PointLights_Locations.at(i).Position, lights.at(i).Position.x, lights.at(i).Position.y, lights.at(i).Position.z);

                        glUniform1f(m_PointLights_Locations.at(i).Constant, lights.at(i).Constant);
                        glUniform1f(m_PointLights_Locations.at(i).Linear, lights.at(i).Linear);
                        glUniform1f(m_PointLights_Locations.at(i).Quadratic, lights.at(i).Quadratic);
                    }
                }
                else
                {
                    DEX_LOG_ERROR("<dex::Shader::Default3D::setPointLights()>: Size of vector of lights inputted is greater than the vector of light locations.");
                }
            }
        private:
            GLuint m_CameraPosition_Location;

            GLuint m_ProjectionViewMatrix_Location;
            GLuint m_ModelMatrix_Location;
            GLuint m_InverseModelMatrix_Location;
            
            GLuint m_BaseColorTextureEnabled_Location;
            GLuint m_BaseColorTextureSampler_Location;
            
            GLuint m_RoughnessTextureEnabled_Location;
            GLuint m_RoughnessTextureSampler_Location;
            
            GLuint m_EmissiveTextureEnabled_Location;
            GLuint m_EmissiveTextureSampler_Location;
            
            GLuint m_AmbientLight_Enabled_Location;
            GLuint m_AmbientLight_Color_Location;
            
            GLuint m_DirectionalLight_Enabled_Location;
            GLuint m_DirectionalLight_Color_Location;
            GLuint m_DirectionalLight_Direction_Location;

            uint32 m_MaxPointLights = 5; // move to light manager later
            std::vector<PointLight_Locations> m_PointLights_Locations;

            uint32 m_TexTilingFactor_Location;
        };
    }
}
