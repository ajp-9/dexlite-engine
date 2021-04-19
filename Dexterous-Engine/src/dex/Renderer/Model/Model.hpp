#pragma once

#include "../Mesh/Mesh.hpp"
#include "../Material/Material.hpp"

namespace dex
{
	struct Model
	{
		Model(std::unique_ptr<Mesh::Base> mesh, std::unique_ptr<Material::Base> material)
			: m_Mesh(std::move(mesh)), m_Material(std::move(material))
		{}

		void render()
		{
			m_Material->setUniforms();
			m_Mesh->render();
		}

		std::unique_ptr<Mesh::Base> m_Mesh;
		std::unique_ptr<Material::Base> m_Material;
	};
}
