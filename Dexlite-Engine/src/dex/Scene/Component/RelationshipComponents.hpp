#pragma once

#include "BaseComponent.hpp"
#include "../Entity/Entity.hpp"

#include <entt.hpp>
#include <vector>

namespace dex
{
    namespace Component
    {
        struct Parent
        {
            Parent() = default;
            Parent(dex::Entity entity)
                : Entity(entity)
            {}
        public:
            dex::Entity Entity;
        };

        struct Children
        {
            Children() = default;
            Children(const std::vector<Entity>& entities)
                : Entities(entities)
            {}
        public:
            std::vector<Entity> Entities;
        };
    }
}
