#pragma once

#include "../../Renderer/Mesh/Mesh.hpp"
#include "../Entity/Entity.hpp"
#include "../../Renderer/Mesh/Material/3D/MaterialAlbedo3D.hpp"

namespace zim
{
	namespace Component
	{
		struct Model
		{
			Model(Mesh<Vertex3D>& mesh, std::unique_ptr<Material::Material> material)
				: m_Mesh(mesh), m_Material(std::move(material))
			{}
			
			void render()
			{
				m_Material->setUniforms();
				m_Mesh.render();
			}

			Mesh<Vertex3D> m_Mesh;
			std::unique_ptr<Material::Material> m_Material;
		};



		struct Model2D
		{
			Model2D(Mesh<Vertex2D>& mesh, std::unique_ptr<Material::Material> material)
				: m_Mesh(mesh), m_Material(std::move(material))
			{}

			void render()
			{
				m_Material->setUniforms();
				m_Mesh.render();
			}

			Mesh<Vertex2D> m_Mesh;
			std::unique_ptr<Material::Material> m_Material;
		};
	}
}
