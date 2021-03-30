#pragma once

#include <glm/mat4x4.hpp>

namespace nim
{
	class PerspectiveCamera
	{
	public:
		// Bounds are: near and far.
		PerspectiveCamera(float fov, glm::uvec2 screenDimensions, glm::vec2 bounds, glm::vec3 position = glm::vec3(0), glm::vec3 rotation = glm::vec3(0));

		void setPosition(const glm::vec3& position) { m_Position = position; calculateViewMatrix(); }
		void setRotation(const glm::vec3& rotation) { m_Rotation = rotation; calculateViewMatrix(); }

		const glm::vec3& getPosition() const { return m_Position; }
		const glm::vec3& getRotation() const { return m_Rotation; }

		const glm::mat4& getProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& getViewMatrix() const { return m_ViewMatrix; }

		const glm::mat4& getProjectionViewMatrix() const { return m_ProjectionViewMatrix; }
	private:
		void calculateViewMatrix();
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;

		glm::mat4 m_ProjectionViewMatrix;

		glm::vec3 m_Position;
		glm::vec3 m_Rotation;

		float fov = 90;
	};
}
