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
        CollisionShape(CollisionShapeType type = CollisionShapeType::NONE) : Type(type) {}
    public:
        CollisionShapeType Type = CollisionShapeType::NONE;
        std::unique_ptr<btCollisionShape> m_BtShape = nullptr;
    };

    class SphereCollisionShape : public CollisionShape
    {
    public:
        SphereCollisionShape(float radius)
            : CollisionShape(CollisionShapeType::SPHERE), Radius(radius)
        {
            m_BtShape = std::make_unique<btSphereShape>(radius);
        }

        float Radius = 0.0f;
    };

    class BoxCollisionShape : public CollisionShape
    {
    public:
        BoxCollisionShape(const glm::vec3& half_extents)
            : CollisionShape(CollisionShapeType::SPHERE), HalfExtents(half_extents)
        {
            m_BtShape = std::make_unique<btBoxShape>(btVector3(half_extents.x, half_extents.y, half_extents.z));
        }

        glm::vec3 HalfExtents = glm::vec3(0.0f);
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
