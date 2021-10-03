#pragma once

#include <glm/mat4x4.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace dex
{
    namespace Component
    {
        struct Transform
        {
            Transform(glm::vec3 position = glm::vec3(0.0f), glm::quat rotation = glm::quat(0.0f, 0.0f, 0.0f, 0.0f), glm::vec3 scale = glm::vec3(1.0f))
                : m_TransformationMatrix(1.0f), m_Position(position), m_Rotation(rotation), m_Scale(scale)
            {
                calculateTransformation();
            }

            void setPosition(const glm::vec3& position) { m_Position = position; calculateTransformation(); }
            void setRotationQuat(const glm::quat& rotation) { m_Rotation = rotation; calculateTransformation(); }
            void setRotationRadians(const glm::vec3& rotation) { m_Rotation = glm::quat(rotation); calculateTransformation(); }
            void setRotationDegrees(const glm::vec3& rotation) { m_Rotation = glm::quat(glm::radians(rotation)); calculateTransformation(); }
            void setScale(const glm::vec3& scale) { m_Scale = scale; calculateTransformation(); }

            void moveBy(const glm::vec3& amount) { m_Position += amount; calculateTransformation(); }
            void rotateByQuat(const glm::quat& amount) { m_Rotation += amount; calculateTransformation(); }
            void rotateByRadians(const glm::vec3& amount) { m_Rotation += glm::quat(amount); calculateTransformation(); }
            void rotateByDegrees(const glm::vec3& amount) { m_Rotation += glm::quat(glm::radians(amount)); calculateTransformation(); }
            void scaleBy(const glm::vec3& amount) { m_Scale += amount; calculateTransformation(); }

            const glm::vec3& getPosition() const { return m_Position; }
            const glm::quat& getRotationQuat() const { return m_Rotation; }
            const glm::vec3& getRotationRadians() const { return glm::eulerAngles(m_Rotation); }
            const glm::vec3& getRotationDegrees() const { return glm::degrees(glm::eulerAngles(m_Rotation)); }
            const glm::vec3& getScale() const { return m_Scale; }
            
            void calculateTransformation();

            const glm::mat4& getTransformationMatrix() const { return m_TransformationMatrix; }

            operator const glm::mat4&() const { return m_TransformationMatrix; }
        private:
            glm::mat4 m_TransformationMatrix;

            glm::vec3 m_Position;
            glm::quat m_Rotation;
            glm::vec3 m_Scale;
        };
    }
}
