#pragma once

#include "Model.hpp"

namespace dex
{
	class ModelManager
	{
	public:
		static void addModel(Model& model);
		static void removeModel(std::string& name);

		static void renderModel(uint32_t id, const glm::mat4& modelMatrix);

		static uint32_t getModelID(std::string& name);
		static const Model& getModel(uint32_t id);
	private:
		static std::vector<Model> s_Models;
	};
}
