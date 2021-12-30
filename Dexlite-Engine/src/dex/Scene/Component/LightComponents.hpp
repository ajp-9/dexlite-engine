#pragma once

#include <glm/vec3.hpp>

#include "../../Renderer/Light/Lights.hpp"
#include "TransformComponent.hpp"
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
                    : Component::Base(entity), dex::Light::Directional(enabled, color, entity.getComponent<Transform>().getRotationRadians())
                {}
            };
        }
    }
}
