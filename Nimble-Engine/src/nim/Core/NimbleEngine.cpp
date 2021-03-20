#include "NimbleEngine.hpp"

#include <sdl2/SDL.h>
#include <chrono>
#include <iostream>
#include <thread>

#include "Program/Program.hpp"
#include "Handle/EngineHandle.hpp"

namespace nim
{
    NimbleEngine::NimbleEngine()
        : m_EngineHandle(std::make_shared<EngineHandle>(*this)),
          m_Application(m_EngineHandle),
          m_DeltaTime(60)
    {}

    NimbleEngine::~NimbleEngine() {}

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
        m_Running = false;
    }
}
