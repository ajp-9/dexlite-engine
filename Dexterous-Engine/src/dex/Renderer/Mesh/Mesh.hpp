#pragma once

#include <vector>

#include "Vertex/Vertex2D.hpp"
#include "Vertex/Vertex3D.hpp"
#include "../VertexArray/VertexArray.hpp"
#include "Material/Material.hpp"

namespace dex
{
	namespace Mesh
	{
		class Mesh
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
		class Mesh_Custom : public Mesh
		{
		public:
			Mesh_Custom() {}
			Mesh_Custom(const std::vector<V>& vertices, const std::vector<uint32_t>& indices)
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
		class Mesh_Albedo2D : public Mesh {};
		class Mesh_Albedo3D : public Mesh {};
		class Mesh_Texture2D : public Mesh {};
		class Mesh_TextureNormal3D : public Mesh_Custom<Vertex_TextureNormal3D>
		{
		public:
			Mesh_TextureNormal3D(const std::vector<Vertex_TextureNormal3D>& vertices, const std::vector<uint32_t>& indices)
				: Mesh_Custom(vertices, indices)
			{}
		};
	}
}
