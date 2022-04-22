#include "Physics.hpp"

#include <glm/glm.hpp>
#include <BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h>
#include "../Util/Logging.hpp"

namespace dex
{
    Physics::Physics(Renderer* renderer)
    {
        m_CollisionConfig     = new btDefaultCollisionConfiguration();
        m_CollisionDispatcher = new btCollisionDispatcher(m_CollisionConfig);
        m_BroadphaseInterface = new btDbvtBroadphase();
        m_CollisionSolver     = new btSequentialImpulseConstraintSolver();
        m_DynamicsWorld       = new btDiscreteDynamicsWorld(m_CollisionDispatcher, m_BroadphaseInterface, m_CollisionSolver, m_CollisionConfig);

        m_DynamicsWorld->setGravity(btVector3(0, -5, 0));

        m_DebugDraw = new DebugDraw(renderer);
        m_DebugDraw->setDebugMode(DebugDraw::DBG_MAX_DEBUG_DRAW_MODE);
        m_DynamicsWorld->setDebugDrawer(m_DebugDraw);
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
        if (DebugEnabled)
            m_DynamicsWorld->debugDrawWorld();
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
