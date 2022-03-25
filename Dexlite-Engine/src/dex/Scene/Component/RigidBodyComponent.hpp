#pragma once

#include <memory>
#include <bullet3/btBulletDynamicsCommon.h>
#include <glm/glm.hpp>

namespace dex
{
    namespace Component
    {
        struct RigidBody
        {
            RigidBody()
            {
                //btRigidBody::btRigidBodyConstructionInfo();
            }

            void setCollisionShape() {}

            float getMass() { return Body->getMass(); }
            void setMass(float mass) { Body->setMassProps(mass, btVector3(0, 0, 0)); }
        public:
            std::unique_ptr<btRigidBody> Body;
        };
    }
}
