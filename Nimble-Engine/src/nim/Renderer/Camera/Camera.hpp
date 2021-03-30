#pragma once

#include <glm/mat4x4.hpp>

namespace nim
{
	class Camera
	{
	public:
		Camera(
			const glm::mat4& projectionMatrix,
			const glm::mat4& viewMatrix = glm::mat4(1.0f),
			const glm::vec3& position = glm::vec3(0.0f),
			const glm::vec3& rotation = glm::vec3(0.0f))
			: m_ProjectionMatrix(projectionMatrix), m_ViewMatrix(viewMatrix), m_Position(position), m_Rotation(rotation)
		{}

		void setPosition(const glm::vec3& position) { m_Position = position; calculateViewMatrix(); }
		void setRotation(const glm::vec3& rotation) { m_Rotation = rotation; calculateViewMatrix(); }

		const glm::vec3& getPosition() const { return m_Position; }
		const glm::vec3& getRotation() const { return m_Rotation; }

		const glm::mat4& getProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& getViewMatrix() const { return m_ViewMatrix; }

		const glm::mat4& getProjectionViewMatrix() const { return m_ProjectionViewMatrix; }
	protected:
		virtual void calculateViewMatrix() = 0;
	protected:
		glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);
		glm::mat4 m_ViewMatrix = glm::mat4(1.0f);

		glm::mat4 m_ProjectionViewMatrix = glm::mat4(1.0f);

		glm::vec3 m_Position = glm::vec3(0.0f);
		glm::vec3 m_Rotation = glm::vec3(0.0f);

		glm::vec3 m_Front = glm::vec3(0.0f, 0.0f, 1.0f);
		glm::vec3 m_Right = glm::vec3(1.0f, 0.0f, 0.0f);
		glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
	};
}
