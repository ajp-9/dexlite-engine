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
            Parent(const Entity& entity)
                : Base(entity) 
            {}
            Parent(const Entity& entity, entt::entity handle)
                : Base(entity), Handle(handle) 
            {}

            entt::entity Handle = entt::null;
        };

        struct ChildrenHandles : Base
        {
            ChildrenHandles(const Entity& entity)
                : Base(entity) 
            {}
            ChildrenHandles(const Entity& entity, const std::vector<entt::entity>& handles)
                : Base(entity), Handles(handles) 
            {}

            std::vector<entt::entity> Handles;
        };
    }
}
