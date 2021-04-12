#pragma once

#include <memory>
#include "../../Shader/Shader.hpp"
#include "../../Texture/Texture.hpp"

namespace zim
{
	struct Material
	{
		Material(const std::weak_ptr<Shader>& shader)
			: m_Shader(shader)
		{}

		virtual void setUniforms() {}

		std::weak_ptr<Shader> m_Shader;
	};
}
