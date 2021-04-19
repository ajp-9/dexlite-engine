#include "Model.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace dex
{
	Model::Model(const char* location)
	{
		std::unique_ptr<Assimp::Importer> importer = std::make_unique<Assimp::Importer>();

		const aiScene* scene = importer->ReadFile(location,
			aiProcess_Triangulate |
			aiProcess_GenNormals |
			aiProcess_OptimizeMeshes |
			aiProcess_JoinIdenticalVertices |
			aiProcess_OptimizeGraph |
			aiProcess_MakeLeftHanded
		);
	}

	void Model::render()
	{
		m_Material->setUniforms();
		m_Mesh->render();
	}
}
