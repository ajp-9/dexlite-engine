#pragma once

#include <glm/glm.hpp>
#include "../../Util/Typedefs.hpp"

namespace dex
{
    enum class CameraType { ORTHOGRAPHIC = 0, PERSPECTIVE = 1 };

    class Camera
    {
    public:
        void setOrthographic(float32 size, float32 near, float32 far);
        void setPerspective(float32 fov, float32 near, float32 far);

        void setPosition(const glm::vec3& position) { m_Position = position; }
        void setRotation(const glm::vec3& rotation) { m_Rotation = rotation; }

        const glm::vec3& getPosition() const { return m_Position; }
        const glm::vec3& getRotation() const { return m_Rotation; }

        const glm::mat4& getViewMatrix() { return m_ViewMatrix; }
        const glm::mat4& getProjectionMatrix() { return m_ProjectionMatrix; }

        const glm::mat4& getProjectionViewMatrix() { return m_ProjectionViewMatrix; }

        // Called everytime you move or rotate the camera.
        void updateViewMatrix();
        // Called everytime you change the screen dimensions or the camera's fov, size, near, or far.
        void updateProjectionMatrix();
    protected:
        CameraType m_Type;

        // Matrices
        glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);
        glm::mat4 m_ViewMatrix = glm::mat4(1.0f);

        glm::mat4 m_ProjectionViewMatrix = glm::mat4(1.0f);

        // Orthographic
        float32 m_Ortho_Size = 1.0f;
        float32 m_Ortho_Near = -1.0f;
        float32 m_Ortho_Far = 1.0f;

        // Perspective
        float32 m_Persp_FOV = glm::radians(45.0f);
        float32 m_Persp_Near = 0.01f;
        float32 m_Persp_Far = 1000.0f;

        // Shared
        glm::vec3 m_Position = glm::vec3(0.0f);
        glm::vec3 m_Rotation = glm::vec3(0.0f);

        glm::vec3 m_Front = glm::vec3(0.0f, 0.0f, 1.0f);
        glm::vec3 m_Right = glm::vec3(1.0f, 0.0f, 0.0f);
        glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f);

        float32 m_AspectRatio = 0.0f;
    };
}
