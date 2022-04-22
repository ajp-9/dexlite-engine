#pragma once

#include <memory>
#include <bullet3/btBulletDynamicsCommon.h>
#include "RigidBody/RigidBody.hpp"
#include "../Util/Transform/BasicTransform.hpp"
#include "Debug/DebugDraw.hpp"

namespace dex
{
    class Physics
    {
        class DebugDraw : public btIDebugDraw
        {
            virtual void drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
            {
                
            }

            virtual void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) {}

            virtual void reportErrorWarning(const char* warningString) {};
            virtual void draw3dText(const btVector3& location, const char* textString) {};
            virtual void setDebugMode(int debugMode) { d = debugMode; }
            virtual int getDebugMode() const { return d; };

            int d = 1;
        };

    public:
        Physics();
        ~Physics();

        void update();

        RigidBody createRigidbody(RigidBodyType type, const std::shared_ptr<CollisionShape>& collision_shape, float mass, const BasicTransform& transform);

        btRigidBody* sbody;
        btRigidBody* floor;

        DebugDraw* m_DebugDraw;

        btDefaultCollisionConfiguration*     m_CollisionConfig;
        btCollisionDispatcher*               m_CollisionDispatcher;
        btBroadphaseInterface*               m_BroadphaseInterface;
        btSequentialImpulseConstraintSolver* m_CollisionSolver;
        btDiscreteDynamicsWorld*             m_DynamicsWorld;
    };
}
