#pragma once

#include "../../Renderer/Model/Model.hpp"

namespace dex
{
	namespace Component
	{
		struct Model : dex::Model
		{
			Model(dex::Model& model)
				: dex::Model(std::move(model))
			{}

			Model(std::unique_ptr<Mesh::Base> mesh, std::unique_ptr<Material::Base> material)
				: dex::Model(std::move(mesh), std::move(material))
			{}
		};
	}
}
