#pragma once

#include <memory>
#include <vector>

#include "Shader.hpp"

namespace nim
{
	class ShaderManager
	{
	public:
		ShaderManager();

		void addShader(const std::shared_ptr<Shader>& shader);
		void removeShader();

		void setUBO();
	private:
		std::vector<std::shared_ptr<Shader>> m_Shaders;
	};
}
