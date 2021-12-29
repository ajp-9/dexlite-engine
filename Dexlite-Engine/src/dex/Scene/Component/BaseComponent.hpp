#pragma once

#include "../Entity/Entity.hpp"

namespace dex
{
    namespace Component
    {
        struct Base
        {
            Base() = default;
        protected:
            Entity m_Entity;
        public:
            friend class dex::Entity;
        };
    }
}
