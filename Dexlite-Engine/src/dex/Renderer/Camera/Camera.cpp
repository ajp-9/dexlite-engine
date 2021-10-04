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
    
    void Camera::updateViewMatrix()
    {
        if (m_Type == CameraType::ORTHOGRAPHIC)
        {
            m_ViewMatrix = glm::translate(glm::mat4(1.0f), m_Position) * glm::toMat4(m_Rotation);
        }
        else if (m_Type == CameraType::PERSPECTIVE)
        {
            //m_Up = glm::normalize(m_Rotation * glm::vec3(0, 1, 0));


            //m_Front.x = cos(m_Rot.x) * cos(m_Rot.y);
            //m_Front.y = sin(m_Rot.y);
            //m_Front.z = sin(m_Rot.x) * cos(m_Rot.y);

            /*glm::vec3& rot_e = glm::eulerAngles(m_Rotation);
            glm::quat QuatAroundX = glm::angleAxis(rot_e.x, glm::vec3(1.0, 0.0, 0.0));
            glm::quat QuatAroundY = glm::angleAxis(rot_e.y, glm::vec3(0.0, 1.0, 0.0));
            glm::quat QuatAroundZ = glm::angleAxis(rot_e.z, glm::vec3(0.0, 0.0, 1.0));
            glm::quat finalOrientation = glm::normalize(QuatAroundX * QuatAroundY * QuatAroundZ);
            m_Rotation = finalOrientation;*/




            //m_Front = glm::normalize(glm::conjugate(m_Rotation) * glm::vec3(0, 0, 1));
            //m_Up = glm::normalize(glm::conjugate(m_Rotation) * glm::vec3(0, 1, 0));

            //glm::vec3 a = glm::degrees(m_Rot);
            //std::cout << a.x << ", " << a.y << ", " << a.z << std::endl;

            //glm::quatLookAt()
            // make position more player relative

            m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
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
