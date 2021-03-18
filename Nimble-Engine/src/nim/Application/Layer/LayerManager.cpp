#include "LayerManager.hpp"

namespace nim
{
	void LayerManager::pushLayer(std::shared_ptr<Layer> layer)
	{
		layer->m_Index = m_Layers.size();
		m_Layers.push_back(layer);
	}

	void LayerManager::popLayer()
	{
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

	void LayerManager::propagateEvent(std::unique_ptr<event::Event>& e)
	{
		for (auto& l : m_Layers)
		{
			l->event(e);

			if (e->m_Handled)
				return;
		}
	}
}
