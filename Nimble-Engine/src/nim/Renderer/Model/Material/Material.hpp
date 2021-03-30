#pragma once

#include <memory>
#include "Shader/Shader.hpp"
#include "Texture/Texture.hpp"

namespace nim
{
	struct Material
	{
		Material(const glm::vec4& albedo)
			: m_Albedo(albedo)
		{}

		glm::vec4 m_Albedo;
		std::shared_ptr<Shader> shader = nullptr;
	};
}
