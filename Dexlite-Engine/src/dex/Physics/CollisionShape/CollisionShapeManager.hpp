#pragma once

#include <memory>
#include <vector>
#include "CollisionShape.hpp"

namespace dex
{
    class CollisionShapeManager
    {
    public:



    private:
        std::shared_ptr<CollisionShape> m_CollisionShapes;
    };
}
