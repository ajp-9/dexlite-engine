#pragma once

#include <memory>
#include <vector>

#include <glm/mat4x4.hpp>
#include "Uniform/UniformBufferObject.hpp"

namespace dex
{
	namespace Shader
	{
		class Base;

		class ShaderManager
		{
		public:
			// Initialize default shader types.
			static void Init();

			static void addShader(const std::shared_ptr<Base>& shader);
			std::weak_ptr<Base> getShader(const char* name);
			static void removeShader(const char* name);
			// Global
			static void setProjectionViewMatrix(const glm::mat4& mat);
		private:
			static std::vector<std::shared_ptr<Base>> m_Shaders;
			static std::vector<UniformBufferObject> m_UBOs;
		};

		enum class Type : uint32_t
		{
			BASE,
			ALBEDO_3D,
			TEXTURE_3D
		};
	}
}
