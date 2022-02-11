#pragma once

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include "../Transform/TransformComponent.hpp"
#include "../../../Util/Typedefs.hpp"
#include "../BaseComponent.hpp"

namespace dex
{
    namespace Component
    {
        class Camera
        {
        public:
            enum class CameraType { ORTHOGRAPHIC = 0, PERSPECTIVE = 1 };
        public:
            Camera() = default;
            // Only 1 camera can be enabled.
            Camera(bool is_enabled)
                : IsEnabled(is_enabled)
            {}

            void setOrthographic(float32 size, float32 near_plane, float32 far_plane);
            void setPerspective(float32 fov, float32 near_plane, float32 far_plane);

            const glm::mat4& getProjectionViewMatrix() { return m_ProjectionViewMatrix; }

            // Called everytime you move or rotate the camera.
            void updateViewMatrix(const Component::Transform& transform);
            // Called everytime you change the screen dimensions or the camera's fov, size, near, or far.
            void updateProjectionMatrix(const glm::vec2& viewport_size);
        private:
            const glm::mat4& getViewMatrix()
            {
                //if (isViewMatrixOld)
                //    updateViewMatrix();

                return m_ViewMatrix;
            }

            const glm::mat4& getProjectionMatrix()
            {
                //if (isProjectionMatrixOld)
                //    updateProjectionMatrix();

                return m_ProjectionMatrix;
            }
        public:
            bool IsEnabled = false;

            CameraType m_Type = CameraType::ORTHOGRAPHIC;
        private:
            bool isViewMatrixOld = true;
            bool isProjectionMatrixOld = true;

            // Matrices

            glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);
            glm::mat4 m_ViewMatrix = glm::mat4(1.0f);
            glm::mat4 m_ProjectionViewMatrix = glm::mat4(1.0f);
        public:
            // Orthographic ---

            float32 m_Ortho_Size = 15.0f;

            // Perspective ---

            float32 m_Persp_FOV = glm::radians(70.0f);

            // Shared ---

            float32 m_Near = 0.01f;
            float32 m_Far = 1000.0f;

            float32 m_AspectRatio = 1.0f;
        };
    }
}
