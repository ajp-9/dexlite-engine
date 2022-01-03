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
                glm::vec3 position = glm::vec3(0.0f),
                glm::vec3 normal = glm::vec3(0.0f),
                glm::vec4 color = glm::vec4(1.0f),
                glm::vec2 texCoord = glm::vec2(0.0f),
                float roughness = 1.0f)

                : // Initializer List:

                Position(position),
                Normal(normal),
                Color(color),
                TexCoord(texCoord),
                Roughness(roughness)
            {}

            static inline const std::vector<Data::Type> getTypes()
            {
                return
                {
                    Data::Type::VEC3,
                    Data::Type::VEC3,
                    Data::Type::VEC4,
                    Data::Type::VEC2,
                    Data::Type::FLOAT
                };
            }

            glm::vec3 Position;
            glm::vec3 Normal;
            glm::vec4 Color;
            glm::vec2 TexCoord;
            float Roughness;
        };

        struct Color
        {
            Color(glm::vec3 position = glm::vec3(0), glm::vec4 color = glm::vec4(1, 0, 1, 1))
                : m_Position(position), m_Color(color)
            {}

            static inline const std::vector<Data::Type> getTypes()
            {
                return
                {
                    Data::Type::VEC3,
                    Data::Type::VEC4
                };
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
