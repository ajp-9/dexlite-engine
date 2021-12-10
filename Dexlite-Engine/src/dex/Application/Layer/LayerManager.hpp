#pragma once

#include <vector>

#include "LayerBase.hpp"
#include "../Event/EventBase.hpp"

namespace dex
{
    class Engine;

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

            friend Engine;
            friend class Window;
        };
    }
}
