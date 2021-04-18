#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include <vector>

#include "../VertexArray/DataTypes.hpp"

namespace dex
{
	struct Vertex3D
	{
		Vertex3D(glm::vec3 position = glm::vec3(0), glm::vec3 normal = glm::vec3(0), glm::vec2 texCoord = glm::vec2(0))
			: m_Position(position), m_Normal(normal), m_TexCoord(texCoord)
		{}

		static const std::vector<Data::Type> getTypes()
		{
			return { Data::Type::VEC3, Data::Type::VEC3, Data::Type::VEC2 };
		}

		glm::vec3 m_Position;
		glm::vec3 m_Normal;
		glm::vec2 m_TexCoord;
	};
	
	struct Vertex_Albedo3D
	{
		Vertex_Albedo3D(glm::vec3 position = glm::vec3(0), glm::vec4 albedo = glm::vec4(1, 0, 1, 1))
			: m_Position(position), m_Albedo(albedo)
		{}

		static const std::vector<Data::Type> getTypes()
		{
			return { Data::Type::VEC3, Data::Type::VEC4 };
		}

		glm::vec3 m_Position;
		glm::vec4 m_Albedo;
	};
	
	struct Vertex_TextureNormal3D
	{
		Vertex_TextureNormal3D(glm::vec3 position = glm::vec3(0), glm::vec3 normal = glm::vec3(0), glm::vec2 texCoord = glm::vec2(0))
			: m_Position(position), m_Normal(normal), m_TexCoord(texCoord)
		{}

		static const std::vector<Data::Type> getTypes()
		{
			return { Data::Type::VEC3, Data::Type::VEC3, Data::Type::VEC2 };
		}

		glm::vec3 m_Position;
		glm::vec3 m_Normal;
		glm::vec2 m_TexCoord;
	};
}
