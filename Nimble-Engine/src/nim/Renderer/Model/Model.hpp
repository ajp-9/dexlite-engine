#pragma once

#include "Material/Material.hpp"
#include "Mesh/Mesh.hpp"

namespace nim
{
	class Model
	{
		Model();

		std::vector<Mesh<Vertex>> m_Meshes;
	};
}
