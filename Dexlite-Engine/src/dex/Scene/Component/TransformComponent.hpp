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
                : m_TransformationMatrix(1.0f), m_ParentTransformationMatrix(1.0f), m_Position(position), m_Rotation(rotation), m_Scale(scale)
            {
                calculateTransformation();
            }

            inline void setPosition(const glm::vec3& position) { m_Position = position; calculateTransformation(); }
            inline void setRotationQuat(const glm::quat& rotation) { m_Rotation = rotation; calculateTransformation(); }
            inline void setRotationEuler(const glm::vec3& rotation) { m_Rotation = glm::quat(rotation); calculateTransformation(); }
            inline void setScale(const glm::vec3& scale) { m_Scale = scale; calculateTransformation(); }

            inline void moveBy(const glm::vec3& amount) { m_Position += amount; calculateTransformation(); }
            inline void rotateByQuat(const glm::quat& amount) { m_Rotation *= amount; calculateTransformation(); }
            inline void rotateByEuler(const glm::vec3& amount) { m_Rotation = glm::normalize(m_Rotation * glm::quat(amount)); calculateTransformation(); }
            inline void scaleBy(const glm::vec3& amount) { m_Scale *= amount; calculateTransformation(); }

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
            inline void moveByLocal(const glm::vec3& amount) { m_Position += (amount.x * m_Right) + (amount.y * m_Up) + (amount.z * m_Forward); calculateTransformation(); }
            inline void rotateByQuatLocal(const glm::quat& amount) { m_Rotation = amount * m_Rotation; calculateTransformation(); }
            inline void rotateByEulerLocal(const glm::vec3& amount) { m_Rotation = glm::quat(amount) * m_Rotation; calculateTransformation(); }
            inline void scaleByLocal(const glm::vec3& amount) { m_Scale = amount * m_Scale; calculateTransformation(); }

            inline const glm::vec3& getPosition() const { return m_Position; }
            inline const glm::quat& getRotationQuat() const { return m_Rotation; }
            inline const glm::vec3& getRotationRadians() const { return glm::eulerAngles(m_Rotation); }
            inline const glm::vec3& getRotationDegrees() const { return glm::degrees(glm::eulerAngles(m_Rotation)); }
            inline const glm::vec3& getScale() const { return m_Scale; }
            
            void calculateTransformation()
            {
                /*
                m_Forward = glm::normalize(glm::conjugate(m_Rotation) * glm::vec3(0, 0, 1));
                m_Up = glm::normalize(glm::conjugate(m_Rotation) * glm::vec3(0, 1, 0));
                m_Right = glm::normalize(glm::conjugate(m_Rotation) * glm::vec3(1, 0, 0));
                */

                m_Forward = m_Rotation * glm::vec3(0, 0, 1);
                m_Up = m_Rotation * glm::vec3(0, 1, 0);
                m_Right = m_Rotation * glm::vec3(1, 0, 0);

                m_TransformationMatrix = 
                    m_ParentTransformationMatrix *
                    glm::translate(glm::mat4(1.0f), m_Position) *
                    glm::toMat4(m_Rotation) *
                    glm::scale(glm::mat4(1.0f), m_Scale);

                m_FlagChanged = true;
            }

            void logAsInfo() const
            {
                auto& eRot = glm::degrees(glm::eulerAngles(m_Rotation));
                
                return DEX_LOG_INFO("Position: (X: {:.1f}, Y: {:.1f}, Z: {:.1f}), Rotation: (X: {:.1f}, Y: {:.1f}, Z: {:.1f}), Scale: (X: {:.1f}, Y: {:.1f}, Z: {:.1f}).",
                    m_Position.x, m_Position.y, m_Position.z,
                    eRot.x, eRot.y, eRot.z,
                    m_Scale.x, m_Scale.y, m_Scale.z);
            }

            /*inline Transform operator+(const Transform& other)
            {
                return Transform(m_Position + other.m_Position, m_Rotation * other.m_Rotation, m_Scale * other.m_Scale);
            }*/

            void setParentTransformationMatrix(glm::mat4& parent_transform_matrix)
            {
                m_ParentTransformationMatrix = parent_transform_matrix;
            }

            /*void resetParentTransformationMatrix()
            {
                m_ParentTransformationMatrix = glm::mat4(1.0f);
            }*/

            inline glm::mat4& getTransformationMatrix() { calculateTransformation(); return m_TransformationMatrix; }

            inline operator const glm::mat4&() const { return m_TransformationMatrix; }

            bool m_FlagChanged = false;
        private:
            glm::mat4 m_TransformationMatrix;

            glm::mat4 m_ParentTransformationMatrix;

            glm::vec3 m_Forward;
            glm::vec3 m_Right;
            glm::vec3 m_Up;

            glm::vec3 m_Position;
            glm::quat m_Rotation;
            glm::vec3 m_Scale;
        };
    }
}
