#include "ModelManager.hpp"

namespace dex
{
	void ModelManager::addModel(Model& model)
	{
		m_Models.push_back(std::move(model));
	}

	void ModelManager::removeModel(std::string& name)
	{
		for (uint32_t i = 0; i < m_Models.size(); i++)
			if (m_Models.at(i).m_Name == name)
				m_Models.erase(m_Models.begin() + i);
	}

	void ModelManager::renderModel(uint32_t id, const glm::mat4& modelMatrix)
	{
		m_Models.at(id).m_Material->m_Shader.lock()->setModelMatrix(modelMatrix);
	}

	uint32_t ModelManager::getModelID(std::string& name)
	{
		for (uint32_t i = 0; i < m_Models.size(); i++)
			if (m_Models.at(i).m_Name == name)
				return i;
	}

	const Model& ModelManager::getModel(uint32_t id)
	{
		return m_Models.at(id);
	}

	/*
	*  Initialize member variables here.
	*/

	std::vector<Model> ModelManager::m_Models;
}
