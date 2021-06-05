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

			virtual void render()
			{
				m_VertexArray.render();
			}

			// Put in the template the type of mesh.
			template <class T>
			inline T& getSelf(Type type)
			{
				if (type == m_Type)
				{
					return *static_cast<T*>(this);
				}
				else
				{
					std::cout << "Error: Mesh ID: " << uint32_t(type) << " class is not a derived class of Mesh::Base\n";
					assert("Error");
					return *static_cast<T*>(this);
				}
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
				const std::vector<Material::Default3D>& materials)
				:
				m_Vertices(vertices),
				m_Indices(indices),
				m_Materials(materials)
			{
				m_Type = Type::INTERFACE;

				m_VertexArray.bind();

				m_VertexArray.m_VertexBuffers.setVertexLayout<V>(V::getTypes());
				m_VertexArray.m_VertexBuffers.uploadData(m_Vertices);

				m_VertexArray.m_IndexBuffer.uploadData(m_Indices);
			}
		protected:
			std::vector<V> m_Vertices;
			std::vector<uint32_t> m_Indices;
			std::vector<M> m_Materials;
		};

		class Default3D : public Interface<Vertex3D::Default, Material::Default3D>
		{
		public:
			Default3D(
				const std::vector<Vertex3D::Default>& vertices,
				const std::vector<uint32_t>& indices,
				const std::vector<Material::Default3D>& materials)
				:
				Interface(vertices, indices, materials)
			{
				m_Type = Type::DEFAULT_3D;
			}
		private:
			std::vector<Material::Default3D> m_Materials;
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
