#pragma once

#include <memory>
#include <bullet3/btBulletDynamicsCommon.h>

namespace dex
{
    class Physics
    {
    public:
        Physics();
        ~Physics();

        void update();

        btRigidBody* sbody;
        btRigidBody* floor;

        btDefaultCollisionConfiguration*     m_CollisionConfig;
        btCollisionDispatcher*               m_CollisionDispatcher;
        btBroadphaseInterface*               m_BroadphaseInterface;
        btSequentialImpulseConstraintSolver* m_CollisionSolver;
        btDiscreteDynamicsWorld*             m_DynamicsWorld;
    };
}
