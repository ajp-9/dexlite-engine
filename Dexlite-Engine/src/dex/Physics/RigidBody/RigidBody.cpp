#include "RigidBody.hpp"

#include "../CollisionShape/CollisionShape.hpp"
#include "../Physics.hpp"

namespace dex
{
    RigidBody::RigidBody(
        RigidBodyType type,
        const std::shared_ptr<dex::CollisionShape>& collision_shape,
        std::unique_ptr<btRigidBody>&& body,
        std::unique_ptr<btMotionState>&& motion_state,
        Physics* physics)
        :
        Type(type),
        Active(true), 
        CollisionShape(collision_shape),
        Body(std::move(body)),
        MotionState(std::move(motion_state)),
        m_Physics(physics)
    {
        Body->setActivationState(Active);
    }

    RigidBody& RigidBody::operator=(RigidBody&& other) noexcept
    {
        if (Body)
            m_Physics->m_DynamicsWorld->removeRigidBody(Body.get());

        Type = other.Type;
        Active = other.Active;
        CollisionShape = other.CollisionShape;
        Body = std::move(other.Body);
        MotionState = std::move(other.MotionState);
        m_Physics = other.m_Physics;

        return *this;
    }

    RigidBody::~RigidBody()
    {
        if (Body)
            m_Physics->m_DynamicsWorld->removeRigidBody(Body.get());
    }
}
