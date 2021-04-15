#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

namespace zim
{
	struct Vertex2D
	{
		Vertex2D(glm::vec3 position = glm::vec3(0), glm::vec3 normal = glm::vec3(0), glm::vec2 texCoord = glm::vec2(0))
			: m_Position(position), m_Normal(normal), m_TexCoord(texCoord)
		{}

		glm::vec3 m_Position;
		glm::vec3 m_Normal;
		glm::vec2 m_TexCoord;
	};
	
	struct Vertex_Albedo2D
	{
		Vertex_Albedo2D(glm::vec3 position = glm::vec3(0), glm::vec4 albedo = glm::vec4(1, 0, 1, 1))
			: m_Position(position), m_Albedo(albedo)
		{}

		glm::vec3 m_Position;
		glm::vec4 m_Albedo;
	};
	
	struct Vertex_Texture2D
	{
		Vertex_Texture2D(glm::vec3 position = glm::vec3(0), glm::vec3 normal = glm::vec3(0), glm::vec2 texCoord = glm::vec2(0))
			: m_Position(position), m_Normal(normal), m_TexCoord(texCoord)
		{}

		glm::vec3 m_Position;
		glm::vec3 m_Normal;
		glm::vec2 m_TexCoord;
	};
}
