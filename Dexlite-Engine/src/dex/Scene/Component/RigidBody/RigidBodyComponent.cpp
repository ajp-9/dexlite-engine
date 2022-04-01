#include "RigidBodyComponent.hpp"

#include "../../../Physics/Physics.hpp"

namespace dex
{
    namespace Component
    {
        RigidBody::RigidBody(Physics* physics, std::shared_ptr<dex::CollisionShape> collision_shape, const glm::vec3& pos, const glm::quat& orient, const float mass)
            : CollisionShape(collision_shape)
        {
            //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
            MotionState = new btDefaultMotionState(btTransform(btQuaternion(orient.x, orient.y, orient.z, orient.w), btVector3(pos.x, pos.y, pos.z)));
            btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, MotionState, collision_shape->m_BtShape, btVector3(1, 1, 1));
            Body = new  btRigidBody(rbInfo);
            //Body->setRestitution(.5);
            physics->m_DynamicsWorld->addRigidBody(Body);
        }
    }
}
