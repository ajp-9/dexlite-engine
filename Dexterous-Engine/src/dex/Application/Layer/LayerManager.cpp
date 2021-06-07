#include "LayerManager.hpp"

#include <functional>

#include "../../Core/Engine.hpp"

namespace dex
{
    namespace Layer
    {
        Manager::Manager()
        {
            //dex::Engine::window.m_Data.m_EventCallbackFunc = std::bind(&Manager::pushEvent, this, std::placeholders::_1);
        }

        void Manager::pushLayer(std::shared_ptr<Base> layer)
        {
            layer->m_Index = m_Layers.size();
            m_Layers.push_back(layer);
            layer->Attach();
        }

        void Manager::popLayer()
        {
            m_Layers.at(m_Layers.size() - 1)->Detach();
            m_Layers.pop_back();
        }

        void Manager::detachAllLayers()
        {
            for (auto it = m_Layers.rbegin(); it != m_Layers.rend(); ++it)
                popLayer();
        }

        // Updating the visually foremost layers first
        void Manager::updateLayers()
        {
            for (auto it = m_Layers.rbegin(); it != m_Layers.rend(); ++it)
            {
                it->get()->update();
            }
        }

        void Manager::renderLayers()
        {
            for (auto& l : m_Layers)
                l->render();
        }

        void Manager::sendEvents()
        {
            /*for (auto& e : m_EventQueue)
            {
                for (std::vector<std::shared_ptr<Base>>::reverse_iterator it = m_Layers.rbegin(); it != m_Layers.rend(); ++it)
                {
                    it->get()->event(e.get());

                    if (e.get().m_Handled)
                        return;
                }
            }*/
        }
    }
}
