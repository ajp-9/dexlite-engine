#include "Physics.hpp"

#include <BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h>
#include "../Util/Logging.hpp"

namespace dex
{
    Physics::Physics()
    {
        m_CollisionConfig     = std::make_unique<btDefaultCollisionConfiguration>();
        m_CollisionDispatcher = std::make_unique<btCollisionDispatcher>(m_CollisionConfig.get());
        m_BroadphaseInterface = std::make_unique<btDbvtBroadphase>();
        m_CollisionSolver     = std::make_unique<btSequentialImpulseConstraintSolver>();
        m_DynamicsWorld       = std::make_unique<btDiscreteDynamicsWorld>(m_CollisionDispatcher.get(), m_BroadphaseInterface.get(), m_CollisionSolver.get(), m_CollisionConfig.get());

        m_DynamicsWorld->setGravity(btVector3(0, -5, 0));


        {
            btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(50.), btScalar(50.), btScalar(50.)));
            //btTriangleMeshShape::
            //btBvhTriangleMeshShape()
            

            //btConvexHullShape();
            

            btTransform groundTransform;
            groundTransform.setIdentity();
            groundTransform.setOrigin(btVector3(0, -56, 0));

            btScalar mass(0.);

            //rigidbody is dynamic if and only if mass is non zero, otherwise static
            bool isDynamic = (mass != 0.f);

            btVector3 localInertia(3000, 0, 0);
            if (isDynamic)
                groundShape->calculateLocalInertia(mass, localInertia);

            //using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
            btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
            btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape, localInertia);
            floor = new btRigidBody(rbInfo);
            floor->setRestitution(1.0f);
            //add the body to the dynamics world
            m_DynamicsWorld->addRigidBody(floor);
        }

        {
            //create a dynamic rigidbody

            btCollisionShape* colShape = new btSphereShape(btScalar(1.4));

            /// Create Dynamic Objects
            btTransform startTransform;
            startTransform.setIdentity();

            btScalar mass(10.f);

            //rigidbody is dynamic if and only if mass is non zero, otherwise static
            bool isDynamic = (mass != 0.f);

            btVector3 localInertia(0, 0, 0);
            if (isDynamic)
                colShape->calculateLocalInertia(mass, localInertia);

            startTransform.setOrigin(btVector3(2, 10, 0));

            //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
            btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
            btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);
            
            sbody = new btRigidBody(rbInfo);
            sbody->setRestitution(.5);
            m_DynamicsWorld->addRigidBody(sbody);
        }


        //m_DynamicsWorld->([](btDynamicsWorld* world, btScalar timeStep) {DEX_LOG_INFO("wat"); });
    }

    void Physics::update()
    {
        m_DynamicsWorld->stepSimulation(1.0f / 60.0f, 10);
        DEX_LOG_INFO(sbody->checkCollideWith(floor));
    }
}
