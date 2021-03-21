#pragma once

#include "Material/Material.hpp"
#include "Mesh/Mesh.hpp"

namespace nim
{
	class Model
	{
		Model();

		std::vector<Mesh> m_Meshes;
		std::vector<Material> m_Materials;
	};
}
