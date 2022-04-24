#pragma once

#include <memory>
#include <bullet3/btBulletDynamicsCommon.h>
#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include "../../Util/Logging.hpp"
#include "../CollisionShape/CollisionShape.hpp"

namespace dex
{
    class Physics;

    enum class RigidBodyType { STATIC, KINEMATIC, DYNAMIC };

    struct RigidBody
    {
        RigidBody() = default;
        RigidBody(
            RigidBodyType type,
            const std::shared_ptr<dex::CollisionShape>& collision_shape,
            std::unique_ptr<btRigidBody>&& body,
            std::unique_ptr<btMotionState>&& motion_state,
            Physics* physics
        );

        RigidBody(RigidBody&& other) noexcept
        {
            operator=(std::move(other));
        }

        RigidBody& operator=(RigidBody&& other) noexcept;

        ~RigidBody();

        void setTransform(const glm::vec3& pos, const glm::quat& orient)
        {
            Body->setWorldTransform(btTransform(btQuaternion(orient.x, orient.y, orient.z, orient.w), btVector3(pos.x, pos.y, pos.z)));
        }

        glm::vec3 getPosition() const
        {
            return glm::vec3(
                Body->getWorldTransform().getOrigin().x(),
                Body->getWorldTransform().getOrigin().y(),
                Body->getWorldTransform().getOrigin().z());
        }

        glm::quat getOrientation() const
        {
            return glm::quat(
                Body->getWorldTransform().getRotation().w(),
                Body->getWorldTransform().getRotation().x(),
                Body->getWorldTransform().getRotation().y(),
                Body->getWorldTransform().getRotation().z());
        }

        void clearAllForces()
        {
            Body->clearForces();
            Body->clearGravity();
        }

        void setCollisionShape() {}

        float getMass() const { return Body->getMass(); }
        void setMass(float mass) { Body->setMassProps(mass, btVector3(0, 0, 0)); }
    public:
        RigidBodyType Type = RigidBodyType::DYNAMIC;
        bool Active = false;

        std::shared_ptr<CollisionShape> CollisionShape = nullptr;

        std::unique_ptr<btRigidBody> Body = nullptr;
        std::unique_ptr<btMotionState> MotionState = nullptr;

        Physics* m_Physics;
    };
}
