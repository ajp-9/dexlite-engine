#include "LayerManager.hpp"

namespace nim
{
	void LayerManager::pushLayer(std::shared_ptr<Layer> layer, std::shared_ptr<EngineHandle>& engineHandle)
	{
		layer->m_Index = m_Layers.size();
		layer->m_EngineHandle = engineHandle;
		m_Layers.push_back(layer);
		layer->attach();
	}

	void LayerManager::popLayer()
	{
		m_Layers.at(m_Layers.size() - 1)->detach();
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

	void LayerManager::setHandle(std::shared_ptr<EngineHandle>& engineHandle) { m_EngineHandle = engineHandle; }
}
