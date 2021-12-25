#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "../../DataTypes/DataTypes.hpp"

namespace dex
{
    namespace Vertex2D
    {
        struct Color
        {
            Color(glm::vec2 position = glm::vec2(0), glm::vec4 color = glm::vec4(1, 0, 1, 1))
                : m_Position(position), m_Color(color)
            {

            }

            static const std::vector<Data::Type> getTypes()
            {
                return { Data::Type::VEC2, Data::Type::VEC4 };
            }

            glm::vec2 m_Position;
            glm::vec4 m_Color;
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
