#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#define NIM_VERTEX_LAYOUT glm::vec3, glm::vec3, glm::vec2

namespace nim
{
	struct Vertex
	{
		Vertex(glm::vec3 position = glm::vec3(0), glm::vec3 normal = glm::vec3(0), glm::vec2 texCoord = glm::vec2(0))
			: m_Position(position), m_Normal(normal), m_TexCoord(texCoord)
		{}

		glm::vec3 m_Position;
		glm::vec3 m_Normal;
		glm::vec2 m_TexCoord;
	};
}
