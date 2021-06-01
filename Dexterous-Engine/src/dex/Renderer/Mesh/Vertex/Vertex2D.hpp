#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "../DataTypes/DataTypes.hpp"

namespace dex
{
	namespace Vertex2D
	{
		struct Diffuse
		{
			Diffuse(glm::vec2 position = glm::vec2(0), glm::vec4 diffuse = glm::vec4(1, 0, 1, 1))
				: m_Position(position), m_Diffuse(diffuse)
			{}

			static const std::vector<Data::Type> getTypes()
			{
				return { Data::Type::VEC2, Data::Type::VEC4 };
			}

			glm::vec2 m_Position;
			glm::vec4 m_Diffuse;
		};

		struct Texture
		{
			Texture(glm::vec2 position = glm::vec2(0), glm::vec2 texCoord = glm::vec2(0))
				: m_Position(position), m_TexCoord(texCoord)
			{}

			static const std::vector<Data::Type> getTypes()
			{
				return { Data::Type::VEC3, Data::Type::VEC2 };
			}

			glm::vec2 m_Position;
			glm::vec2 m_TexCoord;
		};
	}
}
