#include "ModelComponent.hpp"

namespace zim
{
	namespace Component
	{
		Model::Model(Mesh<Vertex>& mesh, const Material& material)
			: m_Mesh(mesh), m_Material(material)
		{
		}

		void Model::render()
		{
			m_Material.setUniforms();
			m_Mesh.render();
		}
	}
}
