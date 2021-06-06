#include "ShaderManager.hpp"

#include "ShaderBase.hpp"
#include "3D/ShaderDefault3D.hpp"

namespace dex
{
	namespace Shader
	{
		Manager::Manager()
		{
			addShader(std::make_shared<Base>());
			addShader(std::make_shared<Default3D>());
		}

		void Manager::addShader(const std::shared_ptr<Shader::Base>& shader)
		{
			m_Shaders.emplace_back(shader);
		}

		std::shared_ptr<Shader::Base>& Manager::getShader(const char* name)
		{
			for (auto& shader : m_Shaders)
				if (shader->getName() == name)
					return shader;
		}

		std::shared_ptr<Base>& Manager::getShader(Type type)
		{
			return m_Shaders.at(uint8_t(type));
		}

		void Manager::setProjectionViewMatrix(const glm::mat4& mat)
		{
			for (auto& shader : m_Shaders)
				shader->setProjectionViewMatrix(mat);
		}
	}
}
