#include "NimbleEngine.hpp"

#include <sdl2/SDL.h>
#include <chrono>
#include <iostream>
#include <thread>

#include "Program/Program.hpp"

namespace nim
{
    void NimbleEngine::Init(std::shared_ptr<Program> program)
    {
        m_Program = program;

        Renderer::Init(glm::uvec4(0, 0, m_Window.getDimensions()));
    }

    void NimbleEngine::Shutdown()
    {
        m_Running = false;

        m_LayerManager.detachAllLayers();
        m_Program->Shutdown();
        Renderer::Shutdown();
    }

    void NimbleEngine::run()
    {
        m_Program->Init();

        m_Running = true;

        while (m_Running)
        {
            m_DeltaTime.start();

            // Updating/events -------------
            Renderer::trySetViewport(glm::uvec4(0, 0, m_Window.getDimensions()));

            m_Program->update();
            m_LayerManager.updateLayers();
            m_LayerManager.sendEvents();

            // Rendering ------------
            Renderer::clear();
            Renderer::beginFrame();

            m_Program->render();

            m_LayerManager.renderLayers();

            Renderer::endFrame();

            // Swap buffers when FINISHED rendering
            m_Window.update();

            m_DeltaTime.sleep();
            m_DeltaTime.end();

            if (!m_Running)
                Shutdown();
        }
    }

    /*
    *  Initialize member variables here.
    */

    bool NimbleEngine::m_Running;

    DeltaTime NimbleEngine::m_DeltaTime(60);
    Window NimbleEngine::m_Window(glm::uvec2(1280, 720));
    LayerManager NimbleEngine::m_LayerManager;

    std::shared_ptr<Program> NimbleEngine::m_Program;
}
