#pragma once

#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>

namespace nim
{
	class OrthographicCamera
	{
	public:
		OrthographicCamera(glm::vec4 bounds, glm::vec3 position, glm::vec3 rotation);

		void setPosition(const glm::vec3& position) { m_Position = position; recalculateViewMatrix(); }
		void setRotation(const glm::vec3& rotation) { m_Rotation = rotation; recalculateViewMatrix(); }

		const glm::vec3& getPosition() const { return m_Position; }
		const glm::vec3& getRotation() const { return m_Rotation; }

		const glm::mat4& getProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& getViewMatrix() const { return m_ViewMatrix; }

		const glm::mat4& getProjectionViewMatrix() const { return m_ProjectionViewMatrix; }
	private:
		void recalculateViewMatrix();
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;

		glm::mat4 m_ProjectionViewMatrix;

		glm::vec3 m_Position;
		glm::vec3 m_Rotation;
	};
}
