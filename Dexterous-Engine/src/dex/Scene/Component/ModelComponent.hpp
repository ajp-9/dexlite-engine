#pragma once

#include "../../Renderer/Model/Model.hpp"

namespace dex
{
    namespace Component
    {
        struct Model : dex::Model
        {
            Model(dex::Model model)
                : dex::Model(std::move(model))
            {}
        };
    }
}
