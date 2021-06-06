#include "ModelManager.hpp"

namespace dex
{
	void ModelManager::addModel(Model& model)
	{
		s_Models.push_back(std::move(model));
	}

	void ModelManager::removeModel(std::string& name)
	{
		for (uint32_t i = 0; i < s_Models.size(); i++)
			if (s_Models.at(i).m_Name == name)
				s_Models.erase(s_Models.begin() + i);
	}

	void ModelManager::renderModel(uint32_t id, const glm::mat4& modelMatrix)
	{
		//s_Models.at(id).m_Material->m_Shader.lock()->setModelMatrix(modelMatrix);
	}

	uint32_t ModelManager::getModelID(std::string& name)
	{
		for (uint32_t i = 0; i < s_Models.size(); i++)
			if (s_Models.at(i).m_Name == name)
				return i;
	}

	const Model& ModelManager::getModel(uint32_t id)
	{
		return s_Models.at(id);
	}

	/*
	*  Initialize member variables here.
	*/

	std::vector<Model> ModelManager::s_Models;
}
