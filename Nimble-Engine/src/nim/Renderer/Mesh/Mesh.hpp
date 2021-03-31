#pragma once

#include <vector>

#include "Vertex.hpp"
#include "../VertexArray/VertexArray.hpp"
#include "Material.hpp"

namespace nim
{
	template <typename V>
	class Mesh
	{
	public:
		Mesh() {}

		void render()
		{
			m_VertexArray.render();
		}
	private:
		std::vector<V> m_Vertices;
		VertexArray<V> m_VertexArray;
	};
}
