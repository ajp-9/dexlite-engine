#pragma once

#include "../Material.hpp"
#include "../Texture/Texture.hpp"
#include "../../Shader/3D/ShaderDefault3D.hpp"

namespace dex
{
	namespace Material
	{
		struct Default3D
		{
			Default3D(const std::weak_ptr<Shader::Default3D>& shader, const std::vector<Texture>& diffuseMaps, std::vector<Texture>& specularMaps)
				: m_Shader(shader), m_DiffuseMaps(diffuseMaps), m_SpecularMaps(specularMaps)
			{}

			std::weak_ptr<Shader::Default3D> m_Shader;
			std::vector<Texture> m_DiffuseMaps;
			std::vector<Texture> m_SpecularMaps;
			// might need color, idk though
		};
	}
}
