#include "ModelComponent.hpp"

namespace zim
{
	namespace Component
	{
		Model::Model(Mesh<Vertex> mesh, const std::weak_ptr<Shader>& shader)
			: m_Mesh(mesh), m_Material(shader)
		{
		}

		void Model::render()
		{
			m_Material.setUniforms();
			m_Mesh.render();
		}
	}
}
