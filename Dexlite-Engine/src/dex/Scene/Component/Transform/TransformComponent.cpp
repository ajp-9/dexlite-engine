#include "TransformComponent.hpp"
#include <glm/gtx/matrix_decompose.hpp>

namespace dex
{
    namespace Component
    {
        void Transform::update(const glm::mat4& parent_transform)
        {
            m_ParentTransformationMatrix = parent_transform;

            m_TransformationMatrix =
                parent_transform *
                glm::translate(glm::mat4(1.0f), m_Position) *
                glm::toMat4(m_Orientation) *
                glm::scale(glm::mat4(1.0f), m_Scale);

            Math::decomposeTransform(m_TransformationMatrix, &m_World_Position, &m_World_Orientation, &m_World_Scale);

            //DEX_LOG_INFO("Did for: {}", m_Entity.getComponent<Component::Tag>().m_Tag);

            //m_FlagChanged = true; // fuck figure it out
        }
    }
}
