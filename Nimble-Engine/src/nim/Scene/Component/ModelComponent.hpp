#pragma once

#include "../../Renderer/Mesh/Mesh.hpp"
#include "../Entity/Entity.hpp"

namespace nim
{
	namespace Component
	{
		// Add <> at tne end to specifiy no paramaters
		struct Model
		{
		public:
			Model();

			void render();

			void addMesh();
			void updateShaders();

			std::vector<Mesh<Vertex>> m_Meshes;
			std::weak_ptr<Shader> m_Shader;
		};
	}
}
