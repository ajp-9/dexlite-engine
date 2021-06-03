#pragma once

#include <vector>

#include "Vertex/Vertex2D.hpp"
#include "Vertex/Vertex3D.hpp"
#include "VertexArray/VertexArray.hpp"

namespace dex
{
	namespace Mesh
	{
		class Base
		{
		public:
			virtual void render()
			{
				m_VertexArray.render();
			}

			// Put in the template the type of mesh.
			template <class T>
			inline T& getSelf()
			{
				return *static_cast<T*>(this);
			}
		protected:
			VertexArray m_VertexArray;
		};

		template <typename V>
		class Interface : public Base
		{
		public:
			Interface() {}
			Interface(const std::vector<V>& vertices, const std::vector<uint32_t>& indices)
				: m_Vertices(vertices), m_Indices(indices)
			{
				m_VertexArray.bind();

				m_VertexArray.m_VertexBuffers.setVertexLayout<V>(V::getTypes());
				m_VertexArray.m_VertexBuffers.uploadData(m_Vertices);

				m_VertexArray.m_IndexBuffer.uploadData(m_Indices);
			}
		protected:
			std::vector<V> m_Vertices;
			std::vector<uint32_t> m_Indices;
		};

		/*class Mesh2D : public Mesh<Vertex2D> {};
		class Mesh3D : public Mesh<Vertex3D> {};*/
		class Color2D : public Interface<Vertex2D::Color> {};
		class Texture2D : public Interface<Vertex2D::Texture> {};
		class Color3D : public Interface<Vertex3D::Color> {};
		class TextureNormal3D : public Interface<Vertex3D::TextureNormal>
		{
		public:
			TextureNormal3D(const std::vector<Vertex3D::TextureNormal>& vertices, const std::vector<uint32_t>& indices)
				: Interface(vertices, indices)
			{}
		};
	}
}
