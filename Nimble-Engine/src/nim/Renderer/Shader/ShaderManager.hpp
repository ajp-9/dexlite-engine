#pragma once

#include "Shader.hpp"
#include <memory>

namespace nim
{
	class ShaderManager
	{
	public:
		ShaderManager();

	private:
		std::shared_ptr<Shader> m_Shaders;
	};
}
