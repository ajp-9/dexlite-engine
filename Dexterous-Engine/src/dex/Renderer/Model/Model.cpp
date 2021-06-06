#include "Model.hpp"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

namespace dex
{
	Model::Model(const char* location)
	{
		Assimp::Importer importer;

		const aiScene* scene = importer.ReadFile(location,
			aiProcess_Triangulate |
			aiProcess_GenNormals |
			aiProcess_OptimizeMeshes |
			aiProcess_JoinIdenticalVertices |
			aiProcess_OptimizeGraph |
			aiProcess_MakeLeftHanded
		);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
		{
			std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << "\n";
			return;
		}

		processNode(scene->mRootNode, scene);
	}

	void Model::render()
	{
		for (auto& mesh : m_Meshes)
		{
			mesh.render();
		}
	}

	void Model::processNode(aiNode* node, const aiScene* scene)
	{
		if (node->mNumMeshes != 1)
			std::cout << "Mesh::processNode : Error! Too many/little meshes.\n";

		// process each mesh located at the current node
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			// the node object only contains indices to index the actual objects in the scene. 
			// the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			processMesh(mesh, scene);
		}
		// after we've processed all of the meshes (if any) we then recursively process each of the children nodes
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			processNode(node->mChildren[i], scene);
		}
	}

	void Model::processMesh(aiMesh* mesh, const aiScene* scene)
	{
		std::vector<Vertex3D::TextureNormal> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture> textures;

		// thru each vertex
		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex3D::TextureNormal vertex;
			glm::vec3 vector; // temp vec
			// positions
			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vertex.m_Position = vector;
			// normals
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.m_Normal = vector;
			// texture coordinates

			if (mesh->mTextureCoords[0])
			{
				glm::vec2 vec;
				// a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
				// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
				vec.x = mesh->mTextureCoords[0][i].x;
				vec.y = mesh->mTextureCoords[0][i].y;
				vertex.m_TexCoord = vec;
			}
			else
			{
				vertex.m_TexCoord = glm::vec2(0.0f, 0.0f);
			}
			vertices.push_back(vertex);
		}

		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			// retrieve all indices of the face and store them in the indices vector
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}

		//m_Mesh = std::make_unique<Mesh::TextureNormal3D>(vertices, indices);
	}
}
