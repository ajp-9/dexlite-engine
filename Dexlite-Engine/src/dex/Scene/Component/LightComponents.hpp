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
            struct Ambient : dex::Light::Ambient, Base
            {
                Ambient(const Entity& entity, bool enabled, const glm::vec3& color)
                    : Component::Base(entity), dex::Light::Ambient(enabled, color)
                {}
            };

            struct Directional : dex::Light::Directional, Base
            {
                Directional(const Entity& entity, bool enabled, const glm::vec3& color)
                    : Component::Base(entity), dex::Light::Directional(enabled, color, glm::vec3(0, -1, 0))
                {}
            };

            struct Point : dex::Light::Point, Base
            {
                Point(const Entity& entity, bool enabled, const glm::vec3& color, float constant, float linear, float quadratic)
                    : Component::Base(entity), dex::Light::Point(enabled, color, entity.getComponent<Transform>().getWorldPosition(), constant, linear, quadratic)
                {}
            };
        }
    }
}
