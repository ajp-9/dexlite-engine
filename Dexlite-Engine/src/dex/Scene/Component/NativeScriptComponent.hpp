#pragma once

#include "BaseComponent.hpp"

namespace dex
{
    namespace Component
    {
        struct NativeScript : Base
        {
            using OnEnableFunction = void(Entity& own_entity);
            using OnDisableFunction = void(Entity& own_entity);
            using OnUpdateFunction = void(Entity& own_entity);

            OnEnableFunction* OnEnableFunction = nullptr;
            OnDisableFunction* OnDisableFunction = nullptr;
            OnUpdateFunction* OnUpdateFunction = nullptr;
        };
    }
}
