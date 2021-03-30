#pragma once

#include <glm/glm.hpp>

namespace nim
{
	namespace Component
	{
		struct Transform
		{
			Transform()
				: m_Transformation(1.0f), m_Position(0), m_Rotation(0), m_Scale(1.0f)
			{
				calculateTransformation();
			}
			Transform(glm::vec3 position, glm::vec3 rotation = glm::vec3(0), glm::vec3 scale = glm::vec3(1.0f))
				: m_Transformation(1.0f), m_Position(position), m_Rotation(rotation), m_Scale(scale)
			{
				calculateTransformation();
			}

			void setPosition(const glm::vec3& position) { m_Position = position; calculateTransformation(); }
			void setRotation(const glm::vec3& rotation) { m_Rotation = rotation; calculateTransformation(); }
			void setScale(const glm::vec3& scale) { m_Scale = scale; calculateTransformation(); }

			const glm::vec3& getPosition() const { return m_Position; }
			const glm::vec3& getRotation() const { return m_Rotation; }
			const glm::vec3& getScale() const { return m_Scale; }

			void calculateTransformation();

			operator const glm::mat4() const { return m_Transformation; }
		private:
			glm::mat4 m_Transformation;

			glm::vec3 m_Position;
			glm::vec3 m_Rotation;
			glm::vec3 m_Scale;
		};
	}
}
