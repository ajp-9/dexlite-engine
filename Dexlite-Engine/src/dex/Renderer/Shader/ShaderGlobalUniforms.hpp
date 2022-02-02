#pragma once

#include <glm/mat4x4.hpp>

#include "../Light/Lights.hpp"
#include <iostream>

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
                setCameraPosition(other.m_CameraPosition);

                setProjectionViewMatrix(other.m_ProjectionViewMatrix);

                setAmbientLight(other.m_AmbientLight);
                setDirectionalLight(other.m_DirectionalLight);
                setPointLights(other.m_PointLights);

                return *this;
            }

            void setAllClean()
            {
                m_IsCameraPositionDirty = false;

                m_IsProjectionViewMatrixDirty = false;
                
                m_IsAmbientLightDirty = false;
                m_IsDirectionalLightDirty = false;
                m_IsPointLightVectorDirty = false;
            }

            // Camera Position:

            void setCameraPosition(const glm::vec3& cam_pos)
            {
                if (m_CameraPosition != cam_pos)
                {
                    m_CameraPosition = cam_pos;
                    m_IsCameraPositionDirty = true;
                }
            }

            const bool isCameraPositionDirty() const { return m_IsCameraPositionDirty; }
            const glm::vec3& getCameraPosition() const { return m_CameraPosition; }

            // Projection-View Matrix:

            void setProjectionViewMatrix(const glm::mat4& proj_view_matrix)
            {
                if (m_ProjectionViewMatrix != proj_view_matrix)
                {
                    m_ProjectionViewMatrix = proj_view_matrix;
                    m_IsProjectionViewMatrixDirty = true;
                }
            }

            const bool isProjectionViewMatrixDirty() const { return m_IsProjectionViewMatrixDirty; }
            const glm::mat4& getProjectionViewMatrix() const { return m_ProjectionViewMatrix; }

            // Ambient Light:

            void setAmbientLight(const Light::Ambient& light)
            {
                if (m_AmbientLight != light)
                {
                    m_AmbientLight = light;
                    m_IsAmbientLightDirty = true;
                }
            }

            const bool isAmbientLightDirty() const { return m_IsAmbientLightDirty; }
            const Light::Ambient& getAmbientLight() const { return m_AmbientLight; }

            // Directional Light:

            inline void setDirectionalLight(const Light::Directional& light)
            {
                if (m_DirectionalLight != light)
                {
                    m_DirectionalLight = light;
                    m_IsDirectionalLightDirty = true;
                }
            }

            const bool isDirectionalLightDirty() const { return m_IsDirectionalLightDirty; }
            const Light::Directional& getDirectionalLight() const { return m_DirectionalLight; }

            // Point Lights:

            void setPointLights(const std::vector<Light::Point>& lights)
            {
                if (m_PointLights != lights)
                {
                    m_PointLights = lights;
                    m_IsPointLightVectorDirty = true;
                }
            }

            const bool isPointLightVectorDirty() const { return m_IsPointLightVectorDirty; }
            const std::vector<Light::Point>& getPointLightVector() const { return m_PointLights; }
        private:
            bool m_IsCameraPositionDirty = true;
            glm::vec3 m_CameraPosition = glm::vec3(0.0f);

            bool m_IsProjectionViewMatrixDirty = true;
            glm::mat4 m_ProjectionViewMatrix = glm::mat4(1.0f);

            bool m_IsAmbientLightDirty = true;
            Light::Ambient m_AmbientLight;

            bool m_IsDirectionalLightDirty = true;
            Light::Directional m_DirectionalLight;

            bool m_IsPointLightVectorDirty = true;
            std::vector<Light::Point> m_PointLights;
        };
    }
}
