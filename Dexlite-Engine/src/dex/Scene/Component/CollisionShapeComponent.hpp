#pragma once

#include <memory>
#include <bullet3/btBulletDynamicsCommon.h>

namespace dex
{
    namespace Component
    {
        struct CollisionShape
        {
            CollisionShape()
            {
                //btConvexHullShape()
            }

            std::unique_ptr<btCollisionShape> Shape;
        };
    }
}
