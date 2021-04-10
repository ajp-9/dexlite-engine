#include "TransformComponent.hpp"

#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace zim
{
	namespace Component
	{
		void Transform::calculateTransformation()
		{
			m_TransformationMatrix = 
				glm::translate(glm::mat4(1.0f), m_Position) *
				glm::toMat4(glm::quat(glm::radians(m_Rotation))) *
				glm::scale(glm::mat4(1.0f), m_Scale);
		}
	}
}
