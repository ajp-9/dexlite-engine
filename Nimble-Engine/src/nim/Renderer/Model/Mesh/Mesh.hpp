#pragma once

#include <vector>

#include "Vertex.hpp"
#include "../../OpenGL/VertexArray/VertexArray.hpp"
#include "../Material/Material.hpp"

namespace nim
{
	template <typename V>
	struct Mesh
	{
		Mesh();
		void render();

		Material material;

		std::vector<V> m_Vertices;
		GL::VertexArray<V> m_VertexArray;
	};
}
