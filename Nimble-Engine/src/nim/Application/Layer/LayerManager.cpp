#include "LayerManager.hpp"

#include <SDL2/SDL.h>

#include "../../Core/NimbleEngine.hpp"
#include "Event/KeyEvent.hpp"
#include "Event/MouseEvent.hpp"

namespace nim
{
	LayerManager::LayerManager()
	{
	}

	void LayerManager::pushLayer(std::shared_ptr<Layer> layer)
	{
		layer->m_Index = m_Layers.size();
		m_Layers.push_back(layer);
		layer->Attach();
	}

	void LayerManager::popLayer()
	{
		m_Layers.at(m_Layers.size() - 1)->Detach();
		m_Layers.pop_back();
	}

	void LayerManager::updateLayers()
	{
		for (auto& l : m_Layers)
			l->update();
	}

	void LayerManager::renderLayers()
	{
		for (auto& l : m_Layers)
			l->render();
	}

	void LayerManager::sendEvents()
	{
		auto events = EventManager::getEventQueue();;

		for (auto& e : events)
		{
			for (std::vector<std::shared_ptr<Layer>>::reverse_iterator it = m_Layers.rbegin(); it != m_Layers.rend(); ++it)
			{
				it->get()->event(e);

				if (e->m_Handled)
					return;
			}
		}
	}
}
