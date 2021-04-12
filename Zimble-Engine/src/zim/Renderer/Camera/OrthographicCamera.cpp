#include "OrthographicCamera.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

namespace zim
{
	OrthographicCamera::OrthographicCamera(glm::vec4 bounds, glm::vec3 position, glm::vec3 rotation)
		: Camera(glm::ortho(bounds.x, bounds.y, bounds.z, bounds.w, -1.0f, 1.0f), glm::mat4(1.0f), position, rotation)
	{
		m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::calculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * glm::toMat4(glm::quat(glm::radians(m_Rotation)));

		m_ViewMatrix = glm::inverse(transform);
		m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}
