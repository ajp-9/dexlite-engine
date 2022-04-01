#pragma once

#include <memory>
#include <bullet3/btBulletDynamicsCommon.h>
#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include "../../../Util/Logging.hpp"
#include "../../../Physics/CollisionMesh/CollisionShape.hpp"

namespace dex
{
    class Physics;

    namespace Component
    {
        struct RigidBody
        {
            RigidBody(Physics* physics, std::shared_ptr<dex::CollisionShape> collision_shape, const glm::vec3& pos, const glm::quat& orient, const float mass);
            /*RigidBody(RigidBody&& other) noexcept = default;

            RigidBody& operator=(RigidBody&& other) noexcept = default;
            ~RigidBody()
            {
                DEX_LOG_INFO("DED");
            }*/
            void setTransform(const glm::vec3& pos, const glm::quat& orient)
            {
                Body->setWorldTransform(btTransform(btQuaternion(orient.x, orient.y, orient.z, orient.w), btVector3(pos.x, pos.y, pos.z)));
            }

            glm::vec3 getPosition()
            {
                return glm::vec3(
                    Body->getWorldTransform().getOrigin().x(),
                    Body->getWorldTransform().getOrigin().y(),
                    Body->getWorldTransform().getOrigin().z());
            }

            glm::quat getOrientation()
            {
                return glm::quat(
                    Body->getWorldTransform().getRotation().w(),
                    Body->getWorldTransform().getRotation().x(),
                    Body->getWorldTransform().getRotation().y(),
                    Body->getWorldTransform().getRotation().z());
            }

            void setCollisionShape() {}

            float getMass() { return Body->getMass(); }
            void setMass(float mass) { Body->setMassProps(mass, btVector3(0, 0, 0)); }
        public:
            btRigidBody*          Body;
            btDefaultMotionState* MotionState;

            std::shared_ptr<CollisionShape> CollisionShape;

            enum class Type { STATIC, KINEMATIC, DYNAMIC } Type = Type::DYNAMIC;
        };
    }
}
