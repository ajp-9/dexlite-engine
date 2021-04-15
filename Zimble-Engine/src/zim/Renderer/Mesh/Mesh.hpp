#pragma once

#include <vector>

#include "Vertex2D.hpp"
#include "Vertex3D.hpp"
#include "../VertexArray/VertexArray.hpp"
#include "Material/Material.hpp"

namespace zim
{
	template <typename V>
	class Mesh
	{
	public:
		Mesh() {}
		Mesh(const std::vector<V>& vertices, const std::vector<uint32_t>& indices)
			: m_Vertices(vertices), m_Indices(indices)
		{
			m_VertexArray.bind();


			m_VertexArray.m_VertexBuffers.setVertexLayout<Vertex3D>(Vertex_TextureNormal3D::getTypes());
			m_VertexArray.m_VertexBuffers.uploadData(m_Vertices);

			m_VertexArray.m_IndexBuffer.uploadData(m_Indices);
		} 

		void render()
		{
			m_VertexArray.render();
		}
	private:
		std::vector<V> m_Vertices;
		std::vector<uint32_t> m_Indices;
		VertexArray m_VertexArray;
	};
}
