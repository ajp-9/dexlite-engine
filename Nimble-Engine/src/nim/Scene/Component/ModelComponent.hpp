#pragma once

#include "../../Renderer/Mesh/Mesh.hpp"
#include "../Entity/Entity.hpp"

namespace nim
{
	namespace Component
	{
		struct Model
		{
		public:
			Model(const std::weak_ptr<Shader>& shader);

			void render();

			Mesh<Vertex> m_Mesh;
			Material m_Material;
		};
	}
}
