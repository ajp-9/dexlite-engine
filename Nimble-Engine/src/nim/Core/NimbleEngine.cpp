#include "NimbleEngine.hpp"

#include <sdl2/SDL.h>
#include <iostream>

namespace nim
{
    NimbleEngine::NimbleEngine(std::shared_ptr<Program> program) : m_Program(program) { }

    NimbleEngine::~NimbleEngine() {}

    void NimbleEngine::run()
    {
        m_Running = true;

        while (m_Running)
        {
            m_Application.update();
        }
    }
}
