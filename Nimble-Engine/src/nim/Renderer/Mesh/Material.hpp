#pragma once

#include <memory>
#include "../Shader/Shader.hpp"
#include "../Texture/Texture.hpp"

namespace nim
{
	struct Material
	{
		Material(const std::weak_ptr<Shader>& shader)
			: m_Shader(shader)
		{}

		void setUniforms()
		{
			//m_Shader.lock()->setAlbedo(m_Albedo);
		}

		glm::vec4 m_Albedo;
		std::weak_ptr<Shader> m_Shader;
	};
}
