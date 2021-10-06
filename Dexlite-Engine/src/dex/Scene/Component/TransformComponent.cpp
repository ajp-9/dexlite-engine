#include "TransformComponent.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include "../../Util/Time/Timer.hpp"

namespace dex
{
    namespace Component
    {
        void Transform::calculateTransformation()
        {
            m_Forward = glm::normalize(glm::conjugate(m_Rotation) * glm::vec3(0, 0, 1));
            m_Up = glm::normalize(glm::conjugate(m_Rotation) * glm::vec3(0, 1, 0));
            m_Right = glm::normalize(glm::conjugate(m_Rotation) * glm::vec3(1, 0, 0));

            m_TransformationMatrix = 
                glm::translate(glm::mat4(1.0f), m_Position) *
                glm::toMat4(m_Rotation) *
                glm::scale(glm::mat4(1.0f), m_Scale);
        }
    }
}
