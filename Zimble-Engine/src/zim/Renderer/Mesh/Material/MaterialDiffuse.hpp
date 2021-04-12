#pragma once

#include "Material.hpp"
#include "../../Texture/Texture.hpp"
#include "../../Shader/ShaderDiffuse.hpp"

namespace zim
{
	class MaterialDiffuse
	{
	public:
		MaterialDiffuse(const std::weak_ptr<ShaderDiffuse>& shader, const Texture& texture)
			: m_Shader(shader), m_DiffuseMap(texture)
		{}
	protected:
		std::weak_ptr<ShaderDiffuse> m_Shader;
		Texture m_DiffuseMap;
	};
}