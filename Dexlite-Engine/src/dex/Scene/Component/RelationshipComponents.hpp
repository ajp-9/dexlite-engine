#pragma once

#include "BaseComponent.hpp"
#include "../Entity/Entity.hpp"

#include <entt.hpp>
#include <vector>

namespace dex
{
    namespace Component
    {
        struct Parent : Base
        {
            Parent(const Entity& own_entity)
                : Base(own_entity)
            {}
            Parent(const Entity& own_entity, dex::Entity entity)
                : Base(own_entity), Entity(entity)
            {}
        public:
            dex::Entity Entity;
        };

        struct Children : Base
        {
            Children(const Entity& own_entity)
                : Base(own_entity)
            {}
            Children(const Entity& own_entity, const std::vector<Entity>& entities)
                : Base(own_entity), Entities(entities)
            {}
        public:
            std::vector<Entity> Entities;
        };
    }
}
