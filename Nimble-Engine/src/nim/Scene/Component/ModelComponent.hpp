#pragma once

#include "../../Renderer/Model/Mesh/Mesh.hpp"
#include "../Entity/Entity.hpp"

namespace nim
{
	namespace Component
	{
		// Add <> at tne end to specifiy no paramaters
		class Model
		{
		public:
			Model();

			void render();

			void addMesh();
			void updateShaders();

			std::vector<std::weak_ptr<Shader>>& getShaders();
		private:
			std::vector<Mesh<Vertex>> m_Meshes;
			std::vector<std::weak_ptr<Shader>> m_Shaders;
		};
	}
}
