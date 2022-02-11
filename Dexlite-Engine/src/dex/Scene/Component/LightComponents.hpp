#pragma once

#include <glm/vec3.hpp>

#include "../../Renderer/Light/Lights.hpp"
#include "Transform/TransformComponent.hpp"
#include "BaseComponent.hpp"

namespace dex
{
    namespace Component
    {
        namespace Light
        {
            struct Ambient : dex::Light::Ambient
            {
                Ambient(bool enabled, const glm::vec3& color)
                    : dex::Light::Ambient(enabled, color)
                {}
            };

            struct Directional : dex::Light::Directional
            {
                Directional(bool enabled, const glm::vec3& color, const glm::vec3& direction)
                    : dex::Light::Directional(enabled, color, direction)
                {}
            };

            struct Point : dex::Light::Point
            {
                Point(bool enabled, const glm::vec3& color, const glm::vec3& world_position, float constant, float linear, float quadratic)
                    : dex::Light::Point(enabled, color, world_position, constant, linear, quadratic)
                {}
            };
        }
    }
}
