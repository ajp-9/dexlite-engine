#pragma once

#include "../../Renderer/Mesh/Mesh.hpp"
#include "../Entity/Entity.hpp"

namespace zim
{
	namespace Component
	{
		struct Model
		{
		public:
			Model(Mesh<Vertex>& mesh, const Material& material);

			void render();

			Mesh<Vertex> m_Mesh;
			Material m_Material;
		};
	}
}
