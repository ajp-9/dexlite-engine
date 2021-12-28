#pragma once

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include "../../Entity/Entity.hpp"
#include "../../../Util/Typedefs.hpp"
#include "../BaseComponent.hpp"

namespace dex
{
    namespace Component
    {
        class Camera : Base
        {
        public:
            enum class CameraType { ORTHOGRAPHIC = 0, PERSPECTIVE = 1 };

            Camera() = default;

            // Only 1 camera can be enabled.
            Camera(bool is_enabled)
                : IsEnabled(is_enabled)
            {}

            void setOrthographic(float32 size, float32 near, float32 far);
            void setPerspective(float32 fov, float32 near, float32 far);

            const glm::mat4& getProjectionViewMatrix() { return m_ProjectionViewMatrix; }

            // Called everytime you move or rotate the camera.
            void updateViewMatrix();
            // Called everytime you change the screen dimensions or the camera's fov, size, near, or far.
            void updateProjectionMatrix();
        private:
            const glm::mat4& getViewMatrix()
            {
                if (isViewMatrixOld)
                    updateViewMatrix();

                return m_ViewMatrix;
            }

            const glm::mat4& getProjectionMatrix()
            {
                if (isProjectionMatrixOld)
                    updateProjectionMatrix();

                return m_ProjectionMatrix;
            }
        public:
            bool IsEnabled = false;
        private:
            CameraType m_Type = CameraType::ORTHOGRAPHIC;

            bool isViewMatrixOld = true;
            bool isProjectionMatrixOld = true;

            // Matrices

            glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);
            glm::mat4 m_ViewMatrix = glm::mat4(1.0f);
            glm::mat4 m_ProjectionViewMatrix = glm::mat4(1.0f);

            // Orthographic ---

            float32 m_Ortho_Size = 15.0f;

            // Perspective ---

            float32 m_Persp_FOV = glm::radians(70.0f);

            // Shared ---

            float32 m_Near = 0.01f;
            float32 m_Far = 1000.0f;

            /*glm::vec3 m_Front = glm::vec3(0.0f, 0.0f, 1.0f);
            glm::vec3 m_Right = glm::vec3(1.0f, 0.0f, 0.0f);
            glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f);*/

            float32 m_AspectRatio = 1.0f;
        public:
            friend class dex::Entity;
        };
    }
}
