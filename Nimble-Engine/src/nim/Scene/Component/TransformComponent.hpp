#pragma once

#include <glm/glm.hpp>

namespace nim
{
	namespace Component
	{
		struct Transform
		{
			Transform()
				: m_Transformation(1.0f), m_Translation(0), m_Rotation(0), m_Scale(0)
			{}
			Transform(glm::vec3 translation, glm::vec3 rotation = glm::vec3(0), glm::vec3 scale = glm::vec3(1.0f))
				: m_Transformation(1.0f), m_Translation(translation), m_Rotation(rotation), m_Scale(scale)
			{}

			void calculateTransformation();

			glm::mat4 m_Transformation;

			glm::vec3 m_Translation;
			glm::vec3 m_Rotation;
			glm::vec3 m_Scale;
		};
	}
}
