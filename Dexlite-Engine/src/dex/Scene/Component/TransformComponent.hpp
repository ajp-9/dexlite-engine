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

            void setParentTransformationMatrix(glm::mat4& parent_transform_matrix)
            {
                m_ParentTransformationMatrix = parent_transform_matrix;

                calculateTransformation();

                m_FlagChanged = true;
            }

            /*void resetParentTransformationMatrix()
            {
                m_ParentTransformationMatrix = glm::mat4(1.0f);
            }*/

            inline glm::mat4& getTransformationMatrix() { return m_TransformationMatrix; }

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
