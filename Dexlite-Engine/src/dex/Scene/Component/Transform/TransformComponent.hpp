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
        struct Transform : Base
        {
            Transform(
                const Entity& entity,
                glm::vec3 position = glm::vec3(0.0f),
                glm::quat rotation = glm::quat(glm::vec3(0.0f)),
                glm::vec3 scale = glm::vec3(1.0f))

                : // Initializer List:
                
                Base(entity),
                m_Position(position),
                m_Rotation(rotation), 
                m_Scale(scale)/*,
                m_WorldPosition(position), 
                m_WorldRotation(rotation),
                m_WorldScale(scale)*/
            {
                m_FlagChanged = true;
            }

            inline void setPosition(const glm::vec3& position) { m_Position = position; m_FlagChanged = true; }
            inline void setRotationQuat(const glm::quat& rotation) { m_Rotation = rotation; m_FlagChanged = true; }
            inline void setRotationEuler(const glm::vec3& rotation) { m_Rotation = glm::quat(rotation); m_FlagChanged = true; }
            inline void setScale(const glm::vec3& scale) { m_Scale = scale; m_FlagChanged = true; }

            inline void moveBy(const glm::vec3& amount) { m_Position += amount; m_FlagChanged = true; }
            inline void rotateByQuat(const glm::quat& amount) { m_Rotation *= amount; m_FlagChanged = true; }
            inline void rotateByEuler(const glm::vec3& amount) { m_Rotation = m_Rotation * glm::quat(amount); m_FlagChanged = true; }
            inline void scaleBy(const glm::vec3& amount) { m_Scale *= amount; m_FlagChanged = true; }

            // Right, Up, and Forward.
            inline void moveByLocal(const glm::vec3& amount) { m_Position += (amount.x * m_Right) + (amount.y * m_Up) + (amount.z * m_Forward); m_FlagChanged = true; }
            inline void rotateByQuatLocal(const glm::quat& amount) { m_Rotation = amount * m_Rotation; m_FlagChanged = true; }
            inline void rotateByEulerLocal(const glm::vec3& amount) { m_Rotation = glm::quat(amount) * m_Rotation; m_FlagChanged = true; }
            inline void scaleByLocal(const glm::vec3& amount) { m_Scale = amount * m_Scale; m_FlagChanged = true; }

            inline const glm::vec3& getPosition() const { return m_Position; }
            inline const glm::quat& getRotationQuat() const { return m_Rotation; }
            inline const glm::vec3 getRotationRadians() const { return glm::eulerAngles(m_Rotation); }
            inline const glm::vec3 getRotationDegrees() const { return glm::degrees(glm::eulerAngles(m_Rotation)); }
            inline const glm::vec3& getScale() const { return m_Scale; }

            inline const glm::vec3 getForward() const { return m_Forward; }
            inline const glm::vec3 getRight() const { return m_Right; }
            inline const glm::vec3 getUp() const { return m_Up; }

            // put in update
            inline const glm::vec3& getWorldPosition() const { return m_World_Position; }
            inline const glm::quat& getWorldRotationQuat() const { return m_World_Rotation; }
            inline const glm::vec3 getWorldRotationRadians() const { return glm::eulerAngles(m_World_Rotation); }
            inline const glm::vec3 getWorldRotationDegrees() const { return glm::degrees(glm::eulerAngles(m_World_Rotation)); }
            inline const glm::vec3& getWorldScale() const { return m_World_Scale; }

            void update();
            
            void logAsInfo() const
            {
                const auto eRot = glm::degrees(glm::eulerAngles(m_Rotation));
                
                return DEX_LOG_INFO("Position: (X: {:.1f}, Y: {:.1f}, Z: {:.1f}), Rotation: (X: {:.1f}, Y: {:.1f}, Z: {:.1f}), Scale: (X: {:.1f}, Y: {:.1f}, Z: {:.1f}).",
                    m_Position.x, m_Position.y, m_Position.z,
                    eRot.x, eRot.y, eRot.z,
                    m_Scale.x, m_Scale.y, m_Scale.z);
            }

            inline const glm::mat4& getTransformationMatrix() const { return m_TransformationMatrix; }

            inline operator const glm::mat4&() const { return m_TransformationMatrix; }
        private:
            inline bool doesEntityHaveParent()
            {
                return m_Entity.hasParent();
            }

            inline const Transform& getParentTransform()
            {
                return m_Entity.getParent().getComponent<Transform>();
            }
        private:
            glm::mat4 m_TransformationMatrix = glm::mat4(1.0f);

            glm::vec3 m_Forward = { 0.0f, 0.0f, 0.0f };
            glm::vec3 m_Right = { 0.0f, 0.0f, 0.0f };
            glm::vec3 m_Up = { 0.0f, 0.0f, 0.0f };
            
            glm::vec3 m_Position;
            glm::quat m_Rotation;
            glm::vec3 m_Scale;

            glm::vec3 m_World_Position;
            glm::quat m_World_Rotation;
            glm::vec3 m_World_Scale;
        public:
            bool m_FlagChanged = false;
        };
    }
}