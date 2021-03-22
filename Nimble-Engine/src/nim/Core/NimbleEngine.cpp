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

        Renderer::Init(m_Window.getDimensions());
    }

    void NimbleEngine::Shutdown()
    {
        m_Running = false;

        Renderer::Shutdown();
        m_Program->End();
    }

    void NimbleEngine::run()
    {
        m_Program->Begin();

        m_Running = true;

        while (m_Running)
        {
            m_DeltaTime.start();

            Renderer::clear();

            m_Window.update();
            m_LayerManager.sendEvents();

            m_Program->update();
            m_Program->render();

            m_DeltaTime.sleep();

            m_DeltaTime.end();
        }

        m_Program->End();
    }

    void NimbleEngine::shutdown()
    {
    }

    /*
    *  Initialize member variables here.
    */

    bool NimbleEngine::m_Running;

    std::shared_ptr<Program> NimbleEngine::m_Program;
    DeltaTime NimbleEngine::m_DeltaTime(60);
    Window NimbleEngine::m_Window(glm::uvec2(300, 300));
    LayerManager NimbleEngine::m_LayerManager;
}
