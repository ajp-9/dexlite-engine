#include "Application.hpp"

#include <SDL2/SDL.h>
#include <iostream>

namespace nim
{
    Application::Application(std::shared_ptr<EngineHandle>& engineHandle)
        : m_Window(glm::ivec2(300, 300)), m_LayerManager(engineHandle)
    {

    }

    void Application::update()
    {
        m_Window.update();
        m_LayerManager.sendEvents();
    }
}
