#pragma once

#include <memory>
#include <vector>

#include "Uniform/UniformBufferObject.hpp"
#include "ShaderBase.hpp"

namespace dex
{
	namespace Shader
	{
		class ShaderManager
		{
		public:
			static void Init() {}

			static void addShader(const std::shared_ptr<Shader::Base>& shader);
			std::weak_ptr<Shader::Base> getShader(const char* name);
			static void removeShader(const char* name);
			// Global
			static void setProjectionViewMatrix(const glm::mat4& mat);
		private:
			static std::vector<std::shared_ptr<Shader::Base>> m_Shaders;
			static std::vector<UniformBufferObject> m_UBOs;
		};
	}
}
