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
        m_DebugDraw->setDebugMode(DebugDraw::DBG_DrawWireframe | DebugDraw::DBG_DrawAabb);
        m_DynamicsWorld->setDebugDrawer(m_DebugDraw);
    }

    Physics::~Physics()
    {
        delete m_DebugDraw;

        delete m_DynamicsWorld;
        delete m_CollisionSolver;
        delete m_BroadphaseInterface;
        delete m_CollisionDispatcher;
        delete m_CollisionConfig;
    }

    void Physics::update()
    {
        m_DynamicsWorld->stepSimulation(1.0f / 60.0f);
        
        if (DebugEnabled)
            m_DynamicsWorld->debugDrawWorld();



    }

    RigidBody Physics::createRigidbody(RigidBodyType type, const std::shared_ptr<CollisionShape>& collision_shape, float mass, const BasicTransform& transform, uint32 id)
    {
        std::unique_ptr<btMotionState> motion_state = std::make_unique<btDefaultMotionState>(
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

        btRigidBody::btRigidBodyConstructionInfo rb_info(mass, motion_state.get(), collision_shape->m_BtShape.get(), btVector3(1, 1, 1));
        std::unique_ptr<btRigidBody> body = std::make_unique<btRigidBody>(rb_info);
        body->setRestitution(.75);
        body->setUserIndex(id);

        m_DynamicsWorld->addRigidBody(body.get());
        
        return RigidBody(type, collision_shape, std::move(body), std::move(motion_state), this);
    }
}
