#pragma once

#include <memory>
#include <vector>

#include "Layer.hpp"

namespace nim
{
	class LayerManager
	{
	public:
		void pushLayer(std::shared_ptr<Layer> layer);
		void popLayer();
	private:
		std::vector<std::shared_ptr<Layer>> m_Layers;
	};
}
