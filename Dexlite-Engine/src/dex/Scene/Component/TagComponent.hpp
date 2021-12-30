#pragma once

#include <string>

#include "BaseComponent.hpp"

namespace dex
{
    namespace Component
    {
        struct Tag : Base
        {
            Tag(const Entity& entity, const std::string& tag)
                : Base(entity), m_Tag(tag)
            {}
        public:
            std::string m_Tag = "";
        };
    }
}
