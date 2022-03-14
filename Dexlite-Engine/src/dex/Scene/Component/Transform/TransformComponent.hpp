#pragma once

#include <glm/mat4x4.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include "../../Entity/Entity.hpp"
#include "../TagComponent.hpp"
#include "../../../Util/Logging.hpp"
#include "../BaseComponent.hpp"
#include "../../../Util/Math/Math.hpp"

namespace dex
{
    namespace Component
    {
        struct Transform
        {
            Transform(
                glm::vec3 position = glm::vec3(0.0f),
                glm::quat rotation = glm::quat(glm::vec3(0.0f)),
                glm::vec3 scale = glm::vec3(1.0f))

                : // Initializer List:
                
                m_Position(position),
                m_Orientation(rotation), 
                m_Scale(scale),
                m_World_Position(position), 
                m_World_Orientation(rotation),
                m_World_Scale(scale)
            {
                m_FlagChanged = true;
            }

            void setPosition(const glm::vec3& position) { m_Position = position; m_FlagChanged = true; }
            void setOrientationQuat(const glm::quat& rotation) { m_Orientation = rotation; m_FlagChanged = true; }
            void setOrientationEuler(const glm::vec3& rotation) { m_Orientation = glm::quat(rotation); m_FlagChanged = true; }
            void setScale(const glm::vec3& scale) { m_Scale = scale; m_FlagChanged = true; }

            void moveBy(const glm::vec3& amount) { m_Position += amount; m_FlagChanged = true; }
            void rotateByQuat(const glm::quat& amount) { m_Orientation = amount * m_Orientation; m_FlagChanged = true; }
            void rotateByEuler(const glm::vec3& amount) { m_Orientation = glm::quat(amount) * m_Orientation; m_FlagChanged = true; }
            void scaleBy(const glm::vec3& amount) { m_Scale = amount * m_Scale; m_FlagChanged = true; }

            // Right, Up, and Forward.
            void moveByLocal(const glm::vec3& amount) { m_Position += (amount.x * m_Right) + (amount.y * m_Up) + (amount.z * m_Forward); m_FlagChanged = true; }
            void rotateByQuatLocal(const glm::quat& amount) { m_Orientation *= amount; m_FlagChanged = true; }
            void rotateByEulerLocal(const glm::vec3& amount) { m_Orientation = m_Orientation * glm::quat(amount); m_FlagChanged = true; }
            void scaleByLocal(const glm::vec3& amount) { m_Scale *= amount; m_FlagChanged = true; }

            const glm::vec3& getPosition() const { return m_Position; }
            const glm::quat& getOrientationQuat() const { return m_Orientation; }
            const glm::vec3 getOrientationRadians() const { return glm::eulerAngles(m_Orientation); }
            const glm::vec3 getOrientationDegrees() const { return glm::degrees(glm::eulerAngles(m_Orientation)); }
            const glm::vec3& getScale() const { return m_Scale; }

            const glm::vec3 getForward() const { return m_Forward; }
            const glm::vec3 getRight() const { return m_Right; }
            const glm::vec3 getUp() const { return m_Up; }

            // put in update
            const glm::vec3& getWorldPosition() const { return m_World_Position; }
            const glm::quat& getWorldOrientationQuat() const { return m_World_Orientation; }
            const glm::vec3 getWorldOrientationRadians() const { return glm::eulerAngles(m_World_Orientation); }
            const glm::vec3 getWorldOrientationDegrees() const { return glm::degrees(glm::eulerAngles(m_World_Orientation)); }
            const glm::vec3& getWorldScale() const { return m_World_Scale; }

            void update(const glm::mat4& parent_transform);
            
            void logAsInfo() const
            {
                const auto eRot = glm::degrees(glm::eulerAngles(m_Orientation));
                
                return DEX_LOG_INFO("Position: (X: {:.1f}, Y: {:.1f}, Z: {:.1f}), Orientation: (X: {:.1f}, Y: {:.1f}, Z: {:.1f}), Scale: (X: {:.1f}, Y: {:.1f}, Z: {:.1f}).",
                    m_Position.x, m_Position.y, m_Position.z,
                    eRot.x, eRot.y, eRot.z,
                    m_Scale.x, m_Scale.y, m_Scale.z);
            }

            const glm::mat4& getTransformationMatrix() const { return m_TransformationMatrix; }

            operator const glm::mat4&() const { return m_TransformationMatrix; }
        public:
            glm::mat4 m_TransformationMatrix = glm::mat4(1.0f);

            glm::mat4 m_ParentTransformationMatrix = glm::mat4(1.0f);

            glm::vec3 m_Forward = { 0.0f, 0.0f, 0.0f };
            glm::vec3 m_Right = { 0.0f, 0.0f, 0.0f };
            glm::vec3 m_Up = { 0.0f, 0.0f, 0.0f };
            
            glm::vec3 m_Position;
            glm::quat m_Orientation;
            glm::vec3 m_Scale;

            glm::vec3 m_World_Position;
            glm::quat m_World_Orientation;
            glm::vec3 m_World_Scale;
        public:
            bool m_FlagChanged = false; // make isDirty
        };
    }
}
