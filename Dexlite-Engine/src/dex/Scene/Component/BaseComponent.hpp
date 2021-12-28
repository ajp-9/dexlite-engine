#pragma once

// make other comp names after like shader3d

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
