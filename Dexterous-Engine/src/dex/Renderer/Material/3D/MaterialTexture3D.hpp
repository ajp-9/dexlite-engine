#pragma once

#include "../Material.hpp"
#include "../Texture/Texture.hpp"
#include "../../Shader/3D/ShaderTexture3D.hpp"

namespace dex
{
	namespace Material
	{
		struct Texture3D
		{
			Texture3D(const std::weak_ptr<Shader::Texture3D>& shader, const Texture& texture)
				: m_Shader(shader), m_DiffuseMap(texture)
			{}

			std::weak_ptr<Shader::Texture3D> m_Shader;
			Texture m_DiffuseMap;
		};
	}
}
