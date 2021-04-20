#pragma once

#include "../Mesh/Mesh.hpp"
#include "../Material/Material.hpp"

#include <assimp/scene.h>

namespace dex
{
	struct Model
	{
		Model(std::unique_ptr<Mesh::Base> mesh, std::unique_ptr<Material::Base> material)
			: m_Mesh(std::move(mesh)), m_Material(std::move(material))
		{}

		// Supported file types:
		// ***.assbin
		// ***.blend
		// ***.fbx
		// ***.obj
		Model(const char* location, std::unique_ptr<Material::Base> material);

		void render();

	private:
		void processNode(aiNode* node, const aiScene* scene);
		void processMesh(aiMesh* mesh, const aiScene* scene);
	public:
		std::string m_Name;

		std::unique_ptr<Mesh::Base> m_Mesh;
		std::unique_ptr<Material::Base> m_Material;
	};
}
