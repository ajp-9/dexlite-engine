#include "CameraComponent.hpp"

#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include "../../../Core/Engine.hpp"

#include "../Transform/TransformComponent.hpp"

namespace dex
{
    namespace Component
    {
        void Camera::setOrthographic(float32 size, float32 near_plane, float32 far_plane)
        {
            m_Type = CameraType::ORTHOGRAPHIC;
            m_Ortho_Size = size;
            m_Near = near_plane;
            m_Far = far_plane;
        }

        void Camera::setPerspective(float32 fov, float32 near_plane, float32 far_plane)
        {
            m_Type = CameraType::PERSPECTIVE;
            m_Persp_FOV = fov;
            m_Near = near_plane;
            m_Far = far_plane;
        }

        void Camera::updateViewMatrix(const Component::Transform& transform)
        {
            if (m_Type == CameraType::ORTHOGRAPHIC)
            {
                m_ViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(transform.getTransformationMatrix()[3])) * glm::toMat4(glm::quat(transform.getTransformationMatrix()));
            }
            else if (m_Type == CameraType::PERSPECTIVE)
            {
                glm::vec3 position = transform.getWorldPosition();

                //m_ViewMatrix = glm::lookAt(position, position + transform.getForward(), transform.getUp());
                m_ViewMatrix = glm::inverse(transform.getTransformationMatrix());
            }
                
            m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;

            isViewMatrixOld = false;
        }

        void Camera::updateProjectionMatrix(const glm::vec2& viewport_size)
        {
            const glm::ivec2& dim = viewport_size;
            m_AspectRatio = float32(dim.x) / float32(dim.y);

            if (m_Type == CameraType::ORTHOGRAPHIC)
            {
                float32 orthoLeft = -m_Ortho_Size * 0.5f;
                float32 orthoRight = m_Ortho_Size * 0.5f;
                float32 orthoBottom = -m_Ortho_Size * 0.5f;
                float32 orthoTop = m_Ortho_Size * 0.5f;

                m_ProjectionMatrix = glm::ortho(orthoLeft * m_AspectRatio, orthoRight * m_AspectRatio, orthoBottom, orthoTop, m_Near, m_Far);
            }
            else if (m_Type == CameraType::PERSPECTIVE)
            {
                m_ProjectionMatrix = glm::perspective(glm::radians(m_Persp_FOV), m_AspectRatio, m_Near, m_Far);
            }

            m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
        }
    }
}
