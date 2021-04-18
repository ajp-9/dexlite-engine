#include "ShaderManager.hpp"

namespace dex
{
	void ShaderManager::addShader(const std::shared_ptr<Shader::Shader>& shader)
	{
		m_Shaders.emplace_back(shader);
	}

	std::weak_ptr<Shader::Shader> ShaderManager::getShader(const char* name)
	{
		for (auto& shader : m_Shaders)
			if (shader->getName() == name)
				return shader;
	}

	void ShaderManager::removeShader(const char* name)
	{
		for (uint32_t i = 0; i < m_Shaders.size(); i++)
			if (m_Shaders.at(i)->getName() == name)
				m_Shaders.erase(m_Shaders.begin() + i);
	}

	void ShaderManager::setProjectionViewMatrix(const glm::mat4& mat)
	{
		for (auto& shader : m_Shaders)
			shader->setProjectionViewMatrix(mat);
	}

	std::vector<std::shared_ptr<Shader::Shader>> ShaderManager::m_Shaders;
}
