#include "TransformComponent.hpp"
#include <glm/gtx/matrix_decompose.hpp>

namespace dex
{
    namespace Component
    {
        void Transform::update(const glm::mat4& parent_transform)
        {
            m_TransformationMatrix =
                parent_transform *
                glm::translate(glm::mat4(1.0f), m_Position) *
                glm::toMat4(m_Orientation) *
                glm::scale(glm::mat4(1.0f), m_Scale);

            m_World_Position    = Math::decomposeTransformToTranslation(m_TransformationMatrix);
            m_World_Orientation = Math::decomposeTransformToOrientation(m_TransformationMatrix);
            m_World_Scale       = Math::decomposeTransformToScale(m_TransformationMatrix);

            m_Forward = m_World_Orientation * glm::vec3(0, 0, 1);
            m_Up      = m_World_Orientation * glm::vec3(0, 1, 0);
            m_Right   = m_World_Orientation * glm::vec3(1, 0, 0);

            //DEX_LOG_INFO("Did for: {}", m_Entity.getComponent<Component::Tag>().m_Tag);

            //m_FlagChanged = true; // fuck figure it out
        }
    }
}
