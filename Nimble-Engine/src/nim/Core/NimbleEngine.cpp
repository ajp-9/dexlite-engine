#include "NimbleEngine.hpp"

#include <sdl2/SDL.h>
#include <iostream>

#include "Program/Program.hpp"
#include "Handle/EngineHandle.hpp"

namespace nim
{
    NimbleEngine::NimbleEngine()
    {
        m_EngineHandle = std::make_shared<EngineHandle>(*this);
    }

    NimbleEngine::~NimbleEngine() {}

    void NimbleEngine::run()
    {
        m_Program->begin();

        m_Running = true;

        while (m_Running)
        {
            m_Application.update();
            m_Program->update();
            m_Program->render();
        }

        m_Program->end();
    }

    void NimbleEngine::shutdown()
    {
        m_Running = false;
    }
}
