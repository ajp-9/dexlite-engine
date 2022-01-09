#pragma once

#include "BaseComponent.hpp"

namespace dex
{
    namespace Component
    {
        struct NativeScript : Base
        {
            using OnEnableFunction = void(Entity& entity);
            using OnDisableFunction = void(Entity& entity);
            using OnUpdateFunction = void(Entity& entity);

            OnEnableFunction* OnEnableFunction = nullptr;
            OnDisableFunction* OnDisableFunction = nullptr;
            OnUpdateFunction* OnUpdateFunction = nullptr;
        };
    }
}
