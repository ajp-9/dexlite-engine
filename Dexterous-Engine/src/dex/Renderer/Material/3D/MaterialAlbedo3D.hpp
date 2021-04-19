#pragma once

#include "../Material.hpp"

namespace dex
{
	namespace Material
	{
		struct Albedo3D : public Base
		{
		public:
			Albedo3D(std::weak_ptr<Shader::Base> shader, glm::vec4 albedo)
				: Base(shader), m_Albedo(albedo)
			{}

			virtual void setUniforms() override {}

			glm::vec4 m_Albedo;
		};
	}
}
