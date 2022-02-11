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
                Ambient() = default;
                Ambient(bool enabled, const glm::vec3& color)
                    : dex::Light::Ambient(enabled, color)
                {}
            };

            struct Directional : dex::Light::Directional
            {
                Directional() = default;
                Directional(bool enabled, const glm::vec3& color)
                    : dex::Light::Directional(enabled, color)
                {}
            };

            struct Point : dex::Light::Point
            {
                Point() = default;
                Point(bool enabled, const glm::vec3& color, float constant, float linear, float quadratic)
                    : dex::Light::Point(enabled, color, constant, linear, quadratic)
                {}
            };
        }
    }
}
