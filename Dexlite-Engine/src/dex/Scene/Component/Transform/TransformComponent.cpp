#include "TransformComponent.hpp"

namespace dex
{
    namespace Component
    {
        void Transform::update()
        {
            if (doesEntityHaveParent())
            {
                auto& parent_transform = m_Entity.getParent().getComponent<Component::Transform>();

                m_TransformationMatrix =
                    parent_transform.m_TransformationMatrix *
                    glm::translate(glm::mat4(1.0f), m_Position) *
                    glm::toMat4(m_Rotation) *
                    glm::scale(glm::mat4(1.0f), m_Scale);
            }
            else
            {
                m_TransformationMatrix =
                    glm::translate(glm::mat4(1.0f), m_Position) *
                    glm::toMat4(m_Rotation) *
                    glm::scale(glm::mat4(1.0f), m_Scale);
            }

            m_Forward = glm::quat(m_TransformationMatrix) * glm::vec3(0, 0, 1);
            m_Up = glm::quat(m_TransformationMatrix) * glm::vec3(0, 1, 0);
            m_Right = glm::quat(m_TransformationMatrix) * glm::vec3(1, 0, 0);

            //DEX_LOG_INFO("Did for: {}", m_Entity.getComponent<Component::Tag>().m_Tag);

            m_FlagChanged = true; // fuck figure it out
        }
    }
}
