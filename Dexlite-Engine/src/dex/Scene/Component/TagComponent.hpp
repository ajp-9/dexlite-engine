#pragma once

#include <string>

#include "BaseComponent.hpp"

namespace dex
{
    namespace Component
    {
        struct Tag
        {
            Tag() = default;
            Tag(const char* tag) : m_Tag(tag) {}
            Tag(const std::string& tag) : m_Tag(tag) {}
        public:
            std::string m_Tag = "";
        };
    }
}
