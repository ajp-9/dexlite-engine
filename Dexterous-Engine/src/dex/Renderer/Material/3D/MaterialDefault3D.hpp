#pragma once

#include "../Material.hpp"
#include "../Texture/Texture.hpp"
#include "../../Shader/3D/ShaderDefault3D.hpp"

namespace dex
{
	namespace Material
	{
		struct Default3D : Base
		{
			Default3D(
				const std::shared_ptr<Shader::Default3D>& shader,
				float texTilingFactor = 1.0f,
				const Texture& diffuseMap = Texture(),
				const Texture& specularMap = Texture())

				: // Initializer List

				Base(shader, Type::DEFAULT_3D),
				m_TexTilingFactor(texTilingFactor),
				m_DiffuseMap(diffuseMap),
				m_SpecularMap(specularMap)
			{}

			virtual void setUniforms()
			{
				auto& tmp_shader = m_Shader->getDerivedSelf<Shader::Default3D>();
				
				if (m_DiffuseMapEnabled)
				{
					tmp_shader.setDiffuseMapEnabled(true);
					tmp_shader.setDiffuseMapSampler();
				}
				else
				{
					tmp_shader.setDiffuseMapEnabled(false);
				}

				if (m_SpecularMapEnabled)
				{
					tmp_shader.setSpecularMapEnabled(true);
					tmp_shader.setSpecularMapLocation();
				}
				else
				{
					tmp_shader.setSpecularMapEnabled(false);
				}
			}
		public:
			float m_TexTilingFactor;

			Texture m_DiffuseMap;
			Texture m_SpecularMap;

			bool m_DiffuseMapEnabled;
			bool m_SpecularMapEnabled;
		};
	}
}
