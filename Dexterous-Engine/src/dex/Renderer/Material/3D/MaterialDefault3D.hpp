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
			Default3D(
				const std::weak_ptr<Shader::Default3D>& shader,
				glm::vec4 color,
				float texTilingFactor,
				const std::vector<Texture>& diffuseMaps,
				const std::vector<Texture>& specularMaps)

				: // Initializer List

				m_Shader(shader),
				m_Color(color),
				m_TexTilingFactor(texTilingFactor),
				m_DiffuseMaps(diffuseMaps),
				m_SpecularMaps(specularMaps)
			{}

			std::weak_ptr<Shader::Default3D> m_Shader;
		
			glm::vec4 m_Color;

			float m_TexTilingFactor;

			std::vector<Texture> m_DiffuseMaps;
			std::vector<Texture> m_SpecularMaps;
		};
	}
}
