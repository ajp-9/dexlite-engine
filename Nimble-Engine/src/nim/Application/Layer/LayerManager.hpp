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
		LayerManager(std::shared_ptr<EngineHandle>& engineHandle);

		void pushLayer(std::shared_ptr<Layer> layer);
		void popLayer();

		void updateLayers();
		void renderLayers();

		void sendEvents();
	private:
		std::vector<std::unique_ptr<event::Event>> getEventQueue();
	private:
		std::vector<std::shared_ptr<Layer>> m_Layers;
		std::shared_ptr<EngineHandle> m_EngineHandle;
	};
}
