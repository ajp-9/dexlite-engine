#include "NimbleEngine.hpp"

#include <sdl2/SDL.h>
#include <iostream>

namespace nim
{
    NimbleEngine::NimbleEngine() {}

    NimbleEngine::~NimbleEngine() {}

    void NimbleEngine::update()
    {
        application.update();
    }
}
