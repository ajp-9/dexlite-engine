#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace nim
{
	namespace component
	{
		struct Transform
		{
			Transform()
				: m_Transformation(1.0f), m_Translation(0), m_Rotation(0), m_Scale(0)
			{}
			Transform(glm::vec3 translation, glm::vec3 rotation = glm::vec3(0), glm::vec3 scale = glm::vec3(1.0f))
				: m_Transformation(1.0f), m_Translation(translation), m_Rotation(rotation), m_Scale(scale)
			{}

			void calculateTransformation()
			{
				m_Transformation = glm::translate(glm::mat4(1.0f), m_Translation) *
								   glm::toMat4(glm::quat(m_Rotation)) *
								   glm::scale(glm::mat4(1.0f), m_Scale);
			}

			glm::mat4 m_Transformation;

			glm::vec3 m_Translation;
			glm::vec3 m_Rotation;
			glm::vec3 m_Scale;
		};
	}
}
