#include "NimbleEngine.hpp"

#include <sdl2/SDL.h>
#include <chrono>
#include <iostream>
#include <thread>

#include "Program/Program.hpp"

namespace nim
{
    void NimbleEngine::Init()
    {

    }

    void NimbleEngine::Shutdown()
    {
        m_Running = false;
    }

    void NimbleEngine::run()
    {
        m_Program->begin();

        m_Running = true;

        while (m_Running)
        {
            m_DeltaTime.start();

            m_Application.update();
            m_Program->update();
            m_Program->render();

            m_DeltaTime.sleep();

            m_DeltaTime.end();
        }

        m_Program->end();
    }

    void NimbleEngine::shutdown()
    {
    }

    /*
    *  Initialize member variables here.
    */

    bool NimbleEngine::m_Running;

    std::shared_ptr<Program> NimbleEngine::m_Program;
    std::shared_ptr<EngineHandle> NimbleEngine::m_EngineHandle;

    DeltaTime NimbleEngine::m_DeltaTime(60);

    Application NimbleEngine::m_Application(glm::ivec2(300, 300));
    Renderer NimbleEngine::m_Renderer;
}
