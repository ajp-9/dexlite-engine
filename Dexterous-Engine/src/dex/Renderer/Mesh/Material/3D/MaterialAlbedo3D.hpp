#pragma once

#include "../Material.hpp"

namespace dex
{
	namespace Material
	{
		struct MaterialAlbedo3D : public Material
		{
		public:
			MaterialAlbedo3D(std::weak_ptr<Shader::Shader> shader, glm::vec4 albedo)
				: Material(shader), m_Albedo(albedo)
			{}

			virtual void setUniforms() override {}

			glm::vec4 m_Albedo;
		};
	}
}
