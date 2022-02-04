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
            Base()
            { 
                m_Type = Type::BASE;
                m_VertexArray.Create();
            }

            ~Base()
            {
                m_VertexArray.Destroy();
            }

            virtual void render() = 0;

            Base(const Base& other) = delete;
            const Base& operator=(const Base& other) = delete;

            Base(Base&& other) noexcept
                : m_Type(other.m_Type), m_VertexArray(std::move(other.m_VertexArray))
            {}

            Base& operator=(Base&& other) noexcept
            {
                if (this != &other)
                {
                    m_Type = other.m_Type;
                    m_VertexArray = std::move(other.m_VertexArray);
                }

                return *this;
            }

            // Put in the template the type of mesh.
            template <class T>
            inline T& getDerivedSelf()
            {
                if (typeid(T) != typeid(*this))
                    std::cout << "Error: The template input: (" << typeid(T).name() << ") can't be derived from the current object (" << typeid(*this).name() << ").\n";

                return *static_cast<T*>(this);
            }
        public:
            Type m_Type;
            VertexArray m_VertexArray;
        };

        template <typename V, typename M>
        class Interface : public Base
        {
        public:
            Interface() = default;

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

            Interface(const Interface& other) = delete;
            const Interface& operator=(const Interface& other) = delete;

            Interface(Interface&& other) noexcept
            {
                m_VertexArray.Destroy();

                m_Type = other.m_Type;
                m_VertexArray = std::move(other.m_VertexArray);
                m_Vertices = std::move(other.m_Vertices);
                m_Indices = std::move(other.m_Indices);
            }

            Interface& operator=(Interface&& other) noexcept
            {
                if (this != &other)
                {
                    m_VertexArray.Destroy();

                    m_Type = other.m_Type;
                    m_VertexArray = std::move(other.m_VertexArray);
                    m_Vertices = std::move(other.m_Vertices);
                    m_Indices = std::move(other.m_Indices);
                }

                return *this;
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
            Default3D() = default;
            Default3D(
                const std::vector<Vertex3D::Default>& vertices,
                const std::vector<uint32_t>& indices)
                :
                Interface(vertices, indices/*Engine::renderer.materialManager.getMaterialDerived<Material::Default3D>("Material::Default3D")*/)// hmmmmm think many meshes need to optimize operation
            {
                m_Type = Type::DEFAULT_3D;
            }

            Default3D(const Default3D& other) = delete;
            const Default3D& operator=(const Default3D& other) = delete;

            Default3D(Default3D&& other) noexcept
                : Interface<Vertex3D::Default, Material::Default3D>(std::move(other))
            {}

            Default3D& operator=(Default3D&& other) noexcept
            {
                if (this != &other)
                {
                    m_Type = other.m_Type;
                    m_VertexArray = std::move(other.m_VertexArray);
                    m_Vertices = std::move(other.m_Vertices);
                    m_Indices = std::move(other.m_Indices);
                }

                return *this;
            }
        };
    }
}
