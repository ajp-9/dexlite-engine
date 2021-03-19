#pragma once

#include <memory>
#include <vector>

#include "Event/Event.hpp"
#include "Layer.hpp"

namespace nim
{
	class EngineHandle;

	class LayerManager
	{
	public:
		void pushLayer(std::shared_ptr<Layer> layer, std::shared_ptr<EngineHandle>& engineHandle);
		void popLayer();

		void updateLayers();
		void renderLayers();
		void propagateEvent(std::unique_ptr<event::Event>& e);
	private:
		std::vector<std::shared_ptr<Layer>> m_Layers;
	};
}
