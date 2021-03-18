#include "NimbleEngine.hpp"

#include <sdl2/SDL.h>
#include <iostream>

#include "Program/Program.hpp"

namespace nim
{
    NimbleEngine::NimbleEngine()
    {
    }

    NimbleEngine::~NimbleEngine() {}

    void NimbleEngine::setProgram(std::shared_ptr<Program> program)
    {
        m_Program = program;
    }

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
}
