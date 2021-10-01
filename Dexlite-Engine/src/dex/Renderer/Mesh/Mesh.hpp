#pragma once

#include <vector>

#include "Vertex/Vertex2D.hpp"
#include "Vertex/Vertex3D.hpp"
#include "VertexArray/VertexArray.hpp"

#include "../Material/3D/MaterialDefault3D.hpp"

namespace dex
{
    namespace Mesh
    {
        enum class Type : uint32
        {
            BASE,
            INTERFACE,
            DEFAULT_3D
        };

        class Base
        {
        public:
            Base() { m_Type = Type::BASE; }

            virtual void render() = 0;

            // Put in the template the type of mesh.
            template <class T>
            inline T& getDerivedSelf()
            {
                if (typeid(T) != typeid(*this))
                    std::cout << "Error: The template input: (" << typeid(T).name() << ") can't be derived from the current object (" << typeid(*this).name() << ").\n";

                return *static_cast<T*>(this);
            }
        public:
            VertexArray m_VertexArray;
            Type m_Type;
        };

        template <typename V, typename M>
        class Interface : public Base
        {
        public:
            Interface() {}
            Interface(
                const std::vector<V>& vertices,
                const std::vector<uint32_t>& indices)
                :
                m_Vertices(vertices),
                m_Indices(indices)
            {
                m_Type = Type::INTERFACE;

                m_VertexArray.bind();

                m_VertexArray.m_VertexBuffers.setVertexLayout<V>(V::getTypes());
                m_VertexArray.m_VertexBuffers.uploadData(m_Vertices);

                m_VertexArray.m_IndexBuffer.uploadData(m_Indices);
            }

            virtual void render()
            {
                m_VertexArray.render();
            }
        public:
            std::vector<V> m_Vertices;
            std::vector<uint32> m_Indices;
        };

        class Default3D : public Interface<Vertex3D::Default, Material::Default3D>
        {
        public:
            Default3D() {}
            Default3D(
                const std::vector<Vertex3D::Default>& vertices,
                const std::vector<uint32_t>& indices)
                :
                Interface(vertices, indices/*Engine::renderer.materialManager.getMaterialDerived<Material::Default3D>("Material::Default3D")*/)// hmmmmm think many meshes need to optimize operation
            {
                m_Type = Type::DEFAULT_3D;
            }
        };
    }
}
