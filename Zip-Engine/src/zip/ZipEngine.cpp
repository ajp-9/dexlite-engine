#include "ZipEngine.hpp"

#include <sdl2/SDL.h>
#include <iostream>

namespace zip
{
    ZipEngine::ZipEngine() {}

    ZipEngine::~ZipEngine() {}

    void ZipEngine::update()
    {
        application.update();
    }
}
