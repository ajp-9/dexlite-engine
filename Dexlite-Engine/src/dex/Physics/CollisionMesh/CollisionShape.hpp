#pragma once

#include <memory>
#include <bullet3/btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionShapes/btShapeHull.h>
#include "../../Renderer/Mesh/Mesh.hpp"

namespace dex
{
    typedef glm::vec3 CollisionMeshVertex;

    enum class CollisionShapeType
    {
        NONE,
        SPHERE,
        BOX,
        CONVEX_HULL,
        TRIANGLE_MESH
    };

    class CollisionShape
    {
    public:
        CollisionShape() {}

        ~CollisionShape()
        {
            if (m_BtShape)
                delete m_BtShape;
        }
    public:
        btCollisionShape* m_BtShape = nullptr;
    };

    class SphereCollisionShape : public CollisionShape
    {
    public:
        SphereCollisionShape(float radius)
        {
            m_BtShape = new btSphereShape(radius);
        }
    };

    class BoxCollisionShape : public CollisionShape
    {
    public:
        BoxCollisionShape(const glm::vec3& half_extents)
        {
            m_BtShape = new btBoxShape(btVector3(half_extents.x, half_extents.y, half_extents.z));
        }
    };

    class ConvexHullCollisionShape : public CollisionShape
    {
    public:
        ConvexHullCollisionShape(const Mesh::Default3D& mesh, const glm::vec3& transform_scale);
    };

    class TriangleMeshCollisionShape : public CollisionShape
    {
    public:
        TriangleMeshCollisionShape(const Mesh::Default3D& mesh, const glm::vec3& transform_scale);
    };
}
