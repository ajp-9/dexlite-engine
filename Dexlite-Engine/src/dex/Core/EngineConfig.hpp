#pragma once

#include <string>
#include <glm/vec2.hpp>

namespace dex
{
    struct EngineConfig
    {
        std::string WindowTitle = "";
        glm::vec2 WindowSize = { 1280, 800 };
    };
}
