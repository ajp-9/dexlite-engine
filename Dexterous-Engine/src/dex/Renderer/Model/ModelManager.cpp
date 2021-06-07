#include "ModelManager.hpp"

namespace dex
{
	void ModelManager::addModel(Model& model)
	{
		s_Models.push_back(std::move(model));
	}

	void ModelManager::removeModel(std::string& name)
	{
		for (uint32 i = 0; i < s_Models.size(); i++)
			if (s_Models.at(i).m_Name == name)
				s_Models.erase(s_Models.begin() + i);
	}

	void ModelManager::renderModel(uint32 id, const glm::mat4& modelMatrix)
	{
		//s_Models.at(id).m_Material->m_Shader.lock()->setModelMatrix(modelMatrix);
	}

	uint32 ModelManager::getModelID(std::string& name)
	{
		for (uint32 i = 0; i < s_Models.size(); i++)
			if (s_Models.at(i).m_Name == name)
				return i;
	}

	const Model& ModelManager::getModel(uint32 id)
	{
		return s_Models.at(id);
	}

	/*
	*  Initialize member variables here.
	*/

	std::vector<Model> ModelManager::s_Models;
}
