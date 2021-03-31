#include "ModelComponent.hpp"

namespace nim
{
	namespace Component
	{
		Model::Model(const std::weak_ptr<Shader>& shader)
			: m_Material(shader)
		{
		}

		void Model::render()
		{
			m_Material.setUniforms();
			m_Mesh.render();
		}
	}
}
