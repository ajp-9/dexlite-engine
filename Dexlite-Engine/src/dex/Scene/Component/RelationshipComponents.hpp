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
            Parent() = default;
            Parent(entt::entity handle) : Handle(handle) {}

            entt::entity Handle = entt::null;
        public:
            friend class dex::Entity;
        };

        struct ChildrenHandles : Base
        {
            ChildrenHandles() = default;
            ChildrenHandles(const std::vector<entt::entity>& handles) : Handles(handles) {}

            std::vector<entt::entity> Handles;
        public:
            friend class dex::Entity;
        };
    }
}
