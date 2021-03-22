#pragma once

#include <memory>
#include <vector>

#include "Event/Event.hpp"
#include "Layer.hpp"
#include "Event/EventManager.hpp"

namespace nim
{
	class LayerManager
	{
		LayerManager();
	public:
		void pushLayer(std::shared_ptr<Layer> layer);
		void popLayer();
	private:
		void updateLayers();
		void renderLayers();
		void sendEvents();
	private:
		std::vector<std::shared_ptr<Layer>> m_Layers;
		EventManager m_EventManager;

		friend class NimbleEngine;
	};
}
