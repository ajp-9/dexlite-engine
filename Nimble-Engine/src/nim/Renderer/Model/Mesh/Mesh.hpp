#pragma once

#include <vector>

#include "Vertex.hpp"
#include "../../OpenGL/VertexArray.hpp"

namespace nim
{
	struct Mesh
	{
		Mesh();
		void render();

		std::vector<Vertex> m_Vertices;
		gl::VertexArray m_VertexArray;
	};
}
