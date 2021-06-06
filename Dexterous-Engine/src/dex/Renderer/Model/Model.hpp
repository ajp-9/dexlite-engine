#pragma once

#include "../Mesh/Mesh.hpp"
#include "../Material/3D/MaterialDefault3D.hpp"

#include <assimp/scene.h>

namespace dex
{
	struct Model
	{
		Model(std::vector<Mesh::Default3D>& meshes)
			: m_Meshes(meshes)
		{}

		// Supported file types:
		// ***.assbin
		// ***.blend
		// ***.fbx
		// ***.obj
		Model(const char* location);

		void render();

	private:
		void processNode(aiNode* node, const aiScene* scene);
		void processMesh(aiMesh* mesh, const aiScene* scene);
	public:
		std::string m_Name;

		std::vector<Mesh::Default3D> m_Meshes;
	};
}
