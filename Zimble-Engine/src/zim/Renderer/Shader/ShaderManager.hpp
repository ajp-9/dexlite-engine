#pragma once

#include <memory>
#include <vector>

#include "Shader.hpp"

namespace zim
{
	class ShaderManager
	{
	public:
		static void Init() {}

		static void addShader(const std::shared_ptr<Shader>& shader);
		std::weak_ptr<Shader> getShader(const char* name);
		static void removeShader(const char* name);
		// Global
		static void setProjectionViewMatrix(const glm::mat4& mat);
	private:
		static std::vector<std::shared_ptr<Shader>> m_Shaders;
	};
}
