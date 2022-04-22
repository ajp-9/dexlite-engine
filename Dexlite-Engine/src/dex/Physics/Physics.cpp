#include "Physics.hpp"

#include <glm/glm.hpp>
#include <BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h>
#include "../Util/Logging.hpp"

namespace dex
{
    Physics::Physics()
    {
        m_CollisionConfig     = new btDefaultCollisionConfiguration();
        m_CollisionDispatcher = new btCollisionDispatcher(m_CollisionConfig);
        m_BroadphaseInterface = new btDbvtBroadphase();
        m_CollisionSolver     = new btSequentialImpulseConstraintSolver();
        m_DynamicsWorld       = new btDiscreteDynamicsWorld(m_CollisionDispatcher, m_BroadphaseInterface, m_CollisionSolver, m_CollisionConfig);

        m_DynamicsWorld->setGravity(btVector3(0, -5, 0));


        DEX_LOG_INFO((uint64)m_DynamicsWorld->getDebugDrawer());
        m_DebugDraw = new DebugDraw();
        //m_DynamicsWorld->setDebugDrawer();


        {
            btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(50.), btScalar(50.), btScalar(50.)));
            //btTriangleMeshShape::
            //btBvhTriangleMeshShape()
            

            //btConvexHullShape();
            

            btTransform groundTransform;
            groundTransform.setIdentity();
            groundTransform.setOrigin(btVector3(0, -56, 0));
            //groundTransform.setRotation(btQuaternion(glm::radians(15.), glm::radians(30.), 0));

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
            floor->setRestitution(.8f);
            //add the body to the dynamics world
            //m_DynamicsWorld->addRigidBody(floor);
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
            sbody->setRestitution(1.5);
            m_DynamicsWorld->addRigidBody(sbody);
        }


        //m_DynamicsWorld->([](btDynamicsWorld* world, btScalar timeStep) {DEX_LOG_INFO("wat"); });
    }

    Physics::~Physics()
    {
        for (int i = m_DynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
        {
            btCollisionObject* obj = m_DynamicsWorld->getCollisionObjectArray()[i];
            btRigidBody* body = btRigidBody::upcast(obj);
            if (body && body->getMotionState())
            {
                delete body->getMotionState();
            }
            m_DynamicsWorld->removeCollisionObject(obj);
            delete obj;
        }

        delete m_DynamicsWorld;
        delete m_CollisionSolver;
        delete m_BroadphaseInterface;
        delete m_CollisionDispatcher;
        delete m_CollisionConfig;
    }

    void Physics::update()
    {
        m_DynamicsWorld->stepSimulation(1.0f / 60.0f);
        //DEX_LOG_INFO(sbody->checkCollideWith(floor));
    }

    RigidBody Physics::createRigidbody(RigidBodyType type, const std::shared_ptr<CollisionShape>& collision_shape, float mass, const BasicTransform& transform)
    {
        btMotionState* motion_state = new btDefaultMotionState(
            btTransform(
                btQuaternion(
                    transform.Orientation.x,
                    transform.Orientation.y,
                    transform.Orientation.z,
                    transform.Orientation.w),
                btVector3(
                    transform.Position.x,
                    transform.Position.y,
                    transform.Position.z)
            ));

        btRigidBody::btRigidBodyConstructionInfo rb_info(mass, motion_state, collision_shape->m_BtShape, btVector3(1, 1, 1));
        btRigidBody* body = new btRigidBody(rb_info);
        body->setRestitution(.75);

        m_DynamicsWorld->addRigidBody(body);

        return RigidBody(body, type, collision_shape);
    }
}
