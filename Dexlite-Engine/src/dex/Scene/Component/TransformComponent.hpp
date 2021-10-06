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
            Transform(glm::vec3 position = glm::vec3(0.0f), glm::quat rotation = glm::quat(glm::vec3(0.0f)), glm::vec3 scale = glm::vec3(1.0f))
                : m_TransformationMatrix(1.0f), m_Position(position), m_Rotation(rotation), m_Scale(scale)
            {
                calculateTransformation();
            }

            void setPosition(const glm::vec3& position) { m_Position = position; calculateTransformation(); }
            void setRotationQuat(const glm::quat& rotation) { m_Rotation = rotation; calculateTransformation(); }
            void setRotationEuler(const glm::vec3& rotation) { m_Rotation = glm::quat(rotation); calculateTransformation(); }
            void setScale(const glm::vec3& scale) { m_Scale = scale; calculateTransformation(); }

            void moveBy(const glm::vec3& amount) { m_Position += amount; calculateTransformation(); }
            void rotateByQuat(const glm::quat& amount) { m_Rotation *= amount; calculateTransformation(); }
            void rotateByEuler(const glm::vec3& amount) { m_Rotation = glm::normalize(m_Rotation * glm::quat(amount)); calculateTransformation(); }
            void scaleBy(const glm::vec3& amount) { m_Scale *= amount; calculateTransformation(); }

            void rotatePitch(float amount)
            {
                m_Rotation = glm::quat(glm::vec3(amount, 0, 0)) * m_Rotation;
                calculateTransformation();
            }
            void rotateYaw(float amount)
            {
                m_Rotation = m_Rotation * glm::quat(glm::vec3(0, amount, 0));
                calculateTransformation();
            }

            // Right, Up, and Forward.
            void moveByLocal(const glm::vec3& amount) { m_Position += (amount.x * m_Right) + (amount.y * m_Up) + (amount.z * m_Forward); calculateTransformation(); }
            void rotateByQuatLocal(const glm::quat& amount) { m_Rotation = amount * m_Rotation; calculateTransformation(); }
            void rotateByEulerLocal(const glm::vec3& amount) { m_Rotation = glm::quat(amount) * m_Rotation; calculateTransformation(); }
            void scaleByLocal(const glm::vec3& amount) { m_Scale = amount * m_Scale; calculateTransformation(); }

            const glm::vec3& getPosition() const { return m_Position; }
            const glm::quat& getRotationQuat() const { return m_Rotation; }
            const glm::vec3& getRotationRadians() const { return glm::eulerAngles(m_Rotation); }
            const glm::vec3& getRotationDegrees() const { return glm::degrees(glm::eulerAngles(m_Rotation)); }
            const glm::vec3& getScale() const { return m_Scale; }
            
            void calculateTransformation();

            const glm::mat4& getTransformationMatrix() const { return m_TransformationMatrix; }

            operator const glm::mat4&() const { return m_TransformationMatrix; }
        private:
        public:
            glm::mat4 m_TransformationMatrix;

            glm::vec3 m_Forward;
            glm::vec3 m_Right;
            glm::vec3 m_Up;

            glm::vec3 m_Position;
            glm::quat m_Rotation;
            glm::vec3 m_Scale;
        };
    }
}
