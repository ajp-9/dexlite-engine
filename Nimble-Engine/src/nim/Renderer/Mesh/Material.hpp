#pragma once

#include <memory>
#include "../Shader/Shader.hpp"
#include "../Texture/Texture.hpp"

namespace nim
{
	struct Material
	{
		Material(const glm::vec4& albedo, const std::weak_ptr<Shader>& shader)
			: m_Albedo(albedo), m_Shader(shader)
		{}

		glm::vec4 m_Albedo;
		std::weak_ptr<Shader> m_Shader;
	};
}
