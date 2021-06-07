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
		enum class Type : uint8_t
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
				const std::vector<uint32_t>& indices,
				const M& material)
				:
				m_Vertices(vertices),
				m_Indices(indices),
				m_Material(material)
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
				//m_Material.
			}
		protected:
			std::vector<V> m_Vertices;
			std::vector<uint32> m_Indices;
			M m_Material;
		};

		class Default3D : public Interface<Vertex3D::Default, Material::Default3D>
		{
		public:
			Default3D(
				const std::vector<Vertex3D::Default>& vertices,
				const std::vector<uint32_t>& indices,
				const Material::Default3D& material)
				:
				Interface(vertices, indices, material)
			{
				m_Type = Type::DEFAULT_3D;
			}
		};

		class TextureNormal3D : public Interface<Vertex3D::Color, Material::Default3D>
		{

		};

		/*class Mesh2D : public Mesh<Vertex2D> {};
		class Mesh3D : public Mesh<Vertex3D> {};
		class Color2D : public Interface<Vertex2D::Color> {};
		class Texture2D : public Interface<Vertex2D::Texture> {};
		class Color3D : public Interface<Vertex3D::Color> {};
		class TextureNormal3D : public Interface<Vertex3D::TextureNormal>
		{
		public:
			TextureNormal3D(const std::vector<Vertex3D::TextureNormal>& vertices, const std::vector<uint32_t>& indices)
				: Interface(vertices, indices)
			{}
		};*/
	}
}
