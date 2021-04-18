#pragma once

#include <memory>
#include <vector>

#include "Event/Event.hpp"
#include "Layer.hpp"
#include "Event/EventManager.hpp"

namespace dex
{
	class LayerManager
	{
		LayerManager();
	public:
		void pushLayer(std::shared_ptr<Layer> layer);
		void popLayer();
		// Detaches all layers from front of the screen to the back.
		void detachAllLayers();
	private:
		void updateLayers();
		void renderLayers();
		void sendEvents();
	private:
		std::vector<std::shared_ptr<Layer>> m_Layers;
		EventManager m_EventManager;

		friend class Engine;
	};
}
