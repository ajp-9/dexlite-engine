#include "Camera.hpp"

#include "../../Core/Engine.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

namespace dex
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

    void Camera::update(const glm::mat4& transformation_matrix)
    {
        if (m_TransformationMatrix != transformation_matrix)
        {
            m_TransformationMatrix = transformation_matrix;

            updateViewMatrix();
        }
    }
    
    void Camera::updateViewMatrix()
    {
        if (m_Type == CameraType::ORTHOGRAPHIC)
        {
            glm::vec3 position = glm::vec3(m_TransformationMatrix[3]);

            m_ViewMatrix = glm::translate(glm::mat4(1.0f), position) * glm::toMat4(glm::quat(m_TransformationMatrix));
        }
        else if (m_Type == CameraType::PERSPECTIVE)
        {
            m_Front = glm::quat(m_TransformationMatrix) * glm::vec3(0, 0, 1);
            m_Up = glm::quat(m_TransformationMatrix) * glm::vec3(0, 1, 0);

            glm::vec3 position = glm::vec3(m_TransformationMatrix[3]);

            m_ViewMatrix = glm::lookAt(position, position + m_Front, m_Up);
        }
        
        m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;

        isViewMatrixOld = false;
    }
    
    void Camera::updateProjectionMatrix()
    {
        glm::ivec2& dim = Engine::window.getDimensions();
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
