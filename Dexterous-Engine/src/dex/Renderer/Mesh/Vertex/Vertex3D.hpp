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
		struct Default
		{
			Default(
				glm::vec3 position = glm::vec3(0),
				glm::vec3 normal = glm::vec3(0),
				glm::vec4 color = glm::vec4(0),
				glm::vec2 texCoord = glm::vec2(0),
				float texTilingFactor = 1.0f,
				float diffuseMapIndex = 0,
				float specularMapIndex = 0)

				: // Initializer List

				m_Position(position),
				m_Normal(normal),
				m_Color(color),
				m_TexCoord(texCoord),
				m_DiffuseMapIndex(diffuseMapIndex),
				m_SpecularMapIndex(specularMapIndex),
				m_TexTilingFactor(texTilingFactor)
			{}

			static const std::vector<Data::Type> getTypes()
			{
				return
				{
					Data::Type::VEC3, 
					Data::Type::VEC3, 
					Data::Type::VEC4,
					Data::Type::VEC2,
					Data::Type::FLOAT, 
					Data::Type::FLOAT
				};
			}

			glm::vec3 m_Position;
			glm::vec3 m_Normal;
			glm::vec4 m_Color;

			glm::vec2 m_TexCoord;
			float m_TexTilingFactor;

			// For indices:
			// Add flat for in/out in glsl so no interpolation.
			// 0 index is for no texture.
			float m_DiffuseMapIndex;
			float m_SpecularMapIndex; 
		};

		struct Color
		{
			Color(glm::vec3 position = glm::vec3(0), glm::vec4 color = glm::vec4(1, 0, 1, 1))
				: m_Position(position), m_Color(color)
			{}

			static const std::vector<Data::Type> getTypes()
			{
				return { Data::Type::VEC3, Data::Type::VEC4 };
			}

			glm::vec3 m_Position;
			glm::vec4 m_Color;
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
