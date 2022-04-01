#pragma once

#include <memory>
#include <bullet3/btBulletDynamicsCommon.h>

namespace dex
{
    enum class CollisionShapeType
    {
        NONE,
        SPHERE,
        BOX,
        CONVEX_HULL,
        TRIANGLE_MESH
    };

    class CollisionShape
    {
    public:
        CollisionShape()
        {

        }

        ~CollisionShape()
        {
            if (m_BtShape)
                delete m_BtShape;
        }
    //protected:
        btCollisionShape* m_BtShape = nullptr;
    };

    class SphereCollisionShape : public CollisionShape
    {
    public:
        SphereCollisionShape(float radius)
        {
            m_BtShape = new btSphereShape(radius);
        }
    };
}
