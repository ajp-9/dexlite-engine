#pragma once

#include "../../Scene/Component/ModelComponent.hpp"

namespace dex
{
    struct ModelLoader
    {
        static Component::Model loadGLTF(const char* location, bool binary);
    };
}
