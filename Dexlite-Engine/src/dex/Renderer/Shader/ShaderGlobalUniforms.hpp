#pragma once

#include <glm/mat4x4.hpp>

#include "../Light/Lights.hpp"

namespace dex
{
    namespace Shader
    {
        class GlobalUniforms
        {
        public:
            GlobalUniforms() = default;

            const GlobalUniforms& operator=(const GlobalUniforms& other)
            {
                setProjectionViewMatrix(other.m_ProjectionViewMatrix);

                setAmbientLight(other.m_AmbientLight);
                setDirectionalLight(other.m_DirectionalLight);

                return *this;
            }

            inline void setAllClean()
            {
                m_IsProjectionViewMatrixDirty = false;
                m_IsAmbientLightDirty = false;
                m_IsDirectionalLightDirty = false;
            }

            // Projection-View Matrix:

            inline void setProjectionViewMatrix(const glm::mat4& proj_view_matrix)
            {
                if (m_ProjectionViewMatrix != proj_view_matrix)
                {
                    m_ProjectionViewMatrix = proj_view_matrix;
                    m_IsProjectionViewMatrixDirty = true;
                }
            }

            inline const bool isProjectionViewMatrixDirty() const { return m_IsProjectionViewMatrixDirty; }
            inline const glm::mat4& getProjectionViewMatrix() const { return m_ProjectionViewMatrix; }

            // Ambient Light:

            inline void setAmbientLight(const Light::Ambient& light)
            {
                if (m_AmbientLight != light)
                {
                    m_AmbientLight = light;
                    m_IsAmbientLightDirty = true;
                }
            }

            inline const bool isAmbientLightDirty() const { return m_IsAmbientLightDirty; }
            inline const Light::Ambient& getAmbientLight() const { return m_AmbientLight; }

            // Directional Light:

            inline void setDirectionalLight(const Light::Directional& light)
            {
                if (m_DirectionalLight != light)
                {
                    m_DirectionalLight = light;
                    m_IsDirectionalLightDirty = true;
                }
            }

            inline const bool isDirectionalLightDirty() const { return m_IsDirectionalLightDirty; }
            inline const Light::Directional& getDirectionalLight() const { return m_DirectionalLight; }
        private:
            bool m_IsProjectionViewMatrixDirty = false;
            glm::mat4 m_ProjectionViewMatrix = glm::mat4(1.0f);

            bool m_IsAmbientLightDirty = false;
            Light::Ambient m_AmbientLight;

            bool m_IsDirectionalLightDirty = false;
            Light::Directional m_DirectionalLight;
        };
    }
}
