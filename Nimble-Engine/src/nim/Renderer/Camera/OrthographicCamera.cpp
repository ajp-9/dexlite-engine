#include "OrthographicCamera.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace nim
{
	OrthographicCamera::OrthographicCamera(glm::vec4 bounds, glm::vec3 position, glm::vec3 rotation)
		: m_ProjectionMatrix(glm::ortho(bounds.x, bounds.y, bounds.z, bounds.w, -1.0f, 1.0f)), m_ViewMatrix(1.0f), m_Position(position), m_Rotation(rotation)
	{
		m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::recalculateViewMatrix()
	{
		glm::mat4 transform =
			glm::translate(glm::mat4(1.0f), m_Position) * 
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.x), glm::vec3(1, 0, 0)) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.y), glm::vec3(0, 1, 0)) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.z), glm::vec3(0, 0, 1));

		m_ViewMatrix = glm::inverse(transform);
		m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}
