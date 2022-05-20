#pragma once

#include <memory>
#include <bullet3/btBulletDynamicsCommon.h>
#include "RigidBody/RigidBody.hpp"
#include "../Util/Transform/BasicTransform.hpp"
#include "Debug/DebugDraw.hpp"

namespace dex
{
    class Renderer;

    class Physics
    {
    public:
        Physics(Renderer* renderer);
        ~Physics();

        void update();

        RigidBody createRigidbody(RigidBodyType type, const std::shared_ptr<CollisionShape>& collision_shape, float mass, const BasicTransform& transform, uint32 id);

        bool DebugEnabled = false;
    public:
        DebugDraw* m_DebugDraw;

        btDefaultCollisionConfiguration*     m_CollisionConfig;
        btCollisionDispatcher*               m_CollisionDispatcher;
        btBroadphaseInterface*               m_BroadphaseInterface;
        btSequentialImpulseConstraintSolver* m_CollisionSolver;
        btDiscreteDynamicsWorld*             m_DynamicsWorld;
    };
}
