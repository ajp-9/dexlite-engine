#pragma once

#include <glm/vec3.hpp>

namespace dex
{
    namespace Component
    {
        struct DirectionalLight
        {
            DirectionalLight()
            {

            }

            //glm::vec3 m_Direction;
            glm::vec3 m_Color;
        };

        struct PointLight
        {
            PointLight()
            {

            }

            //glm::vec3 m_Position;
            glm::vec3 m_Color;
        };
    }
}
