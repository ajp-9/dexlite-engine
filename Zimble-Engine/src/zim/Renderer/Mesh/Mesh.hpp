#pragma once

#include <vector>

#include "Vertex.hpp"
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

			m_VertexArray.m_VertexBuffers.setVertexLayout<zim::Vertex>({ Data::Type::VEC3, Data::Type::VEC3, Data::Type::VEC2 });
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
