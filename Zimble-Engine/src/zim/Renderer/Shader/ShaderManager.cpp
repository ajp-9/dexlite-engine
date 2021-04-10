#include "ShaderManager.hpp"

namespace zim
{
	ShaderManager::ShaderManager()
	{
	}

	void ShaderManager::addShader(const std::shared_ptr<Shader>& shader)
	{
		m_Shaders.emplace_back(shader);
	}

	void ShaderManager::removeShader()
	{
	}

	void ShaderManager::setUBO()
	{
	}
}
