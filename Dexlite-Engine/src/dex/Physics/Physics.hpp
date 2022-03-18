#pragma once

#include <memory>
#include <bullet3/btBulletDynamicsCommon.h>

namespace dex
{
    class Physics
    {
    public:
        Physics();

        void update();

        btRigidBody* sbody;

        std::unique_ptr<btDefaultCollisionConfiguration> m_CollisionConfig;
        std::unique_ptr<btCollisionDispatcher> m_CollisionDispatcher;
        std::unique_ptr<btBroadphaseInterface> m_BroadphaseInterface;
        std::unique_ptr<btSequentialImpulseConstraintSolver> m_CollisionSolver;
        std::unique_ptr<btDiscreteDynamicsWorld> m_DynamicsWorld;
    };
}
