#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include <vector>

#include "../../DataTypes/DataTypes.hpp"

namespace dex
{
	namespace Vertex3D
	{
		struct Diffuse
		{
			Diffuse(glm::vec3 position = glm::vec3(0), glm::vec4 diffuse = glm::vec4(1, 0, 1, 1))
				: m_Position(position), m_Diffuse(diffuse)
			{}

			static const std::vector<Data::Type> getTypes()
			{
				return { Data::Type::VEC3, Data::Type::VEC4 };
			}

			glm::vec3 m_Position;
			glm::vec4 m_Diffuse;
		};

		struct TextureNormal
		{
			TextureNormal(glm::vec3 position = glm::vec3(0), glm::vec3 normal = glm::vec3(0), glm::vec2 texCoord = glm::vec2(0))
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
}
