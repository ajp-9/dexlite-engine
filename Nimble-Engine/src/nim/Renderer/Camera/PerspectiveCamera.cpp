#include "PerspectiveCamera.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

namespace nim
{
	PerspectiveCamera::PerspectiveCamera(float fov, glm::uvec2 screenDimensions, glm::vec2 bounds, glm::vec3 position, glm::vec3 rotation)
		: m_ProjectionMatrix(glm::perspective(glm::radians(fov), float(screenDimensions.x) / float(screenDimensions.y), bounds.x, bounds.y)),
		m_ViewMatrix(1.0f),
		m_Position(position),
		m_Rotation(rotation)
	{
		m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void PerspectiveCamera::calculateViewMatrix()
	{
		glm::mat4 transform =
			glm::translate(glm::mat4(1.0f), m_Position) * glm::toMat4(glm::quat(glm::radians(m_Rotation)));

		m_ViewMatrix = glm::inverse(transform);
		m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}
