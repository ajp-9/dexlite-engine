#include "ShaderDefault3D.hpp"

#include <spdlog/fmt/fmt.h>

namespace dex
{
    namespace Shader
    {
        Default3D::Default3D(const std::string& src)
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

            for (uint32 i = 0; i < m_MaxPointLights; i++)
            {
                PointLight_Locations pointLight_Locations;

                pointLight_Locations.Enabled = glGetUniformLocation(m_ProgramID, fmt::format("u_PointLights[{}].Enabled", i).c_str());
                pointLight_Locations.Color = glGetUniformLocation(m_ProgramID, fmt::format("u_PointLights[{}].Color", i).c_str());
                pointLight_Locations.Position = glGetUniformLocation(m_ProgramID, fmt::format("u_PointLights[{}].Position", i).c_str());
                pointLight_Locations.Constant = glGetUniformLocation(m_ProgramID, fmt::format("u_PointLights[{}].Constant", i).c_str());
                pointLight_Locations.Linear = glGetUniformLocation(m_ProgramID, fmt::format("u_PointLights[{}].Linear", i).c_str());
                pointLight_Locations.Quadratic = glGetUniformLocation(m_ProgramID, fmt::format("u_PointLights[{}].Quadratic", i).c_str());

                m_PointLights_Locations.push_back(pointLight_Locations);
            }
        }

        void Default3D::setLocations3D()
        {
            m_CameraPosition_Location = glGetUniformLocation(m_ProgramID, "u_CameraPosition");

            m_ProjectionViewMatrix_Location = glGetUniformLocation(m_ProgramID, "u_ProjectionViewMatrix");
            m_ModelMatrix_Location = glGetUniformLocation(m_ProgramID, "u_ModelMatrix");
            m_InverseModelMatrix_Location = glGetUniformLocation(m_ProgramID, "u_InverseModelMatrix");
        }

        void Default3D::updateGlobalUniforms(const GlobalUniforms& global_uniforms)
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

            if (global_uniforms.isPointLightVectorDirty())
                setPointLights(global_uniforms.getPointLightVector());
        }
    }
}
