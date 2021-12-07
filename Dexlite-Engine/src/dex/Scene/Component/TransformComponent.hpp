#pragma once

#include <glm/mat4x4.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include "../../Util/Logging.hpp"

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

            Transform operator+(const Transform& other)
            {
                return Transform(m_Position + other.m_Position, m_Rotation * other.m_Position, m_Scale * other.m_Scale);
            }

            void setPosition(const glm::vec3& position) { m_Position = position; calculateTransformation(); }
            void setRotationQuat(const glm::quat& rotation) { m_Rotation = rotation; calculateTransformation(); }
            void setRotationEuler(const glm::vec3& rotation) { m_Rotation = glm::quat(rotation); calculateTransformation(); }
            void setScale(const glm::vec3& scale) { m_Scale = scale; calculateTransformation(); }

            void moveBy(const glm::vec3& amount) { m_Position += amount; calculateTransformation(); }
            void rotateByQuat(const glm::quat& amount) { m_Rotation *= amount; calculateTransformation(); }
            void rotateByEuler(const glm::vec3& amount) { m_Rotation = glm::normalize(m_Rotation * glm::quat(amount)); calculateTransformation(); }
            void scaleBy(const glm::vec3& amount) { m_Scale *= amount; calculateTransformation(); }

            /*void rotatePitchNYawBy(float pitch_amount, float yaw_amount)
            {
                auto rot_euler_deg = glm::degrees(glm::eulerAngles(m_Rotation));
                auto rot_after_pitch = glm::quat(glm::vec3(pitch_amount, 0, 0)) * m_Rotation;

                auto what = glm::degrees(glm::eulerAngles(glm::inverse(m_Rotation)));

                //DEX_LOG_WARN("{0:0.2f}, {1:0.2f}, {2:0.2f}, {2:0.2f}", rot_after_pitch.x, rot_after_pitch.y, rot_after_pitch.z, rot_after_pitch.w);
                //DEX_LOG_WARN("{0:0.3f}, {1:0.3f}, {2:0.3f}", rot_euler_deg.x, rot_euler_deg.y, rot_euler_deg.z);
                //DEX_LOG_WARN("{0:0.3f}, {1:0.3f}, {2:0.3f}", m_Forward.x, m_Forward.y, m_Forward.z);
                DEX_LOG_WARN("{0:0.3f}, {1:0.3f}, {2:0.3f}", what.x, what.y, what.z);

                if (rot_euler_deg.x + pitch_amount > 90 && rot_euler_deg.y > 0)
                    "t";
                //else
                    m_Rotation = glm::quat(glm::vec3(pitch_amount, 0, 0)) * m_Rotation;

                m_Rotation = m_Rotation * glm::quat(glm::vec3(0, yaw_amount, 0));

                calculateTransformation();
            }

            // Useful for FPS Cameras. Will stop rotating pitch at +/- 90 degrees;
            void rotatePitchEuler(float amount)
            {
                //if (glm::degrees(glm::eulerAngles(m_Rotation).x) + glm::degrees(amount) > 90)
                //    m_Rotation = glm::quat(90)

                m_Rotation = glm::quat(glm::vec3(amount, 0, 0)) * m_Rotation;
                calculateTransformation();
            }

            void rotateYawEuler(float amount)
            {
                m_Rotation = m_Rotation * glm::quat(glm::vec3(0, amount, 0));
                calculateTransformation();
            }*/

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
