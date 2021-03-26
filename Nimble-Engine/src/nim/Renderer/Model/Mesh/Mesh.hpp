#pragma once

#include <vector>

#include "Vertex.hpp"
#include "../../OpenGL/VertexArray/VertexArray.hpp"

namespace nim
{
	struct Mesh
	{
		Mesh();
		void render();

		std::vector<Vertex> m_Vertices;
		gl::VertexArray<Vertex> m_VertexArray;
	};
}
