#pragma once

#include "../Material.hpp"

namespace dex
{
	namespace Material
	{
		struct Diffuse3D : public Base
		{
		public:
			Diffuse3D(std::weak_ptr<Shader::Base> shader, glm::vec4 diffuse)
				: Base(shader), m_Diffuse(diffuse)
			{}

			virtual void setUniforms() override {}

			glm::vec4 m_Diffuse;
		};
	}
}
