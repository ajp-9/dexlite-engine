#include "ModelComponent.hpp"

namespace nim
{
	namespace Component
	{
		Model::Model()
		{
		}

		void Model::render()
		{
			for (auto& m : m_Meshes)
			{
				m.render();
			}
		}

		void Model::addMesh()
		{

			updateShaders();
		}

		void Model::updateShaders()
		{
			std::vector<std::weak_ptr<Shader>> shaders;

			for (auto& m : m_Meshes)
			{
				shaders.emplace_back(m.getShader());
			}

			m_Shaders = shaders;
		}

		std::vector<std::weak_ptr<Shader>>& Model::getShaders()
		{
			return m_Shaders;
		}
	}
}