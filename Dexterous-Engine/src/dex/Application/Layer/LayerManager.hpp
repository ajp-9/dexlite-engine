#pragma once

#include <memory>
#include <vector>

#include "Event/EventBase.hpp"
#include "LayerBase.hpp"
#include "Event/EventManager.hpp"

namespace dex
{
	namespace Layer
	{
		class Manager
		{
			Manager();
		public:
			void pushLayer(std::shared_ptr<Base> layer);
			void popLayer();
			// Detaches all layers from front of the screen to the back.
			void detachAllLayers();
		private:
			void updateLayers();
			void renderLayers();
			void sendEvents();
		private:
			std::vector<std::shared_ptr<Base>> m_Layers;
			Event::Manager m_EventManager;

			friend class Engine;
		};
	}
}
