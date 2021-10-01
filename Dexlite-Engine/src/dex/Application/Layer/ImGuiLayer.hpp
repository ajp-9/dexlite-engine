#pragma once

#include "LayerBase.hpp"

namespace dex
{
    class ImGuiLayer : public Layer::Base
    {
        // Inherited via Layer
        // possibly move imgui api to here
        virtual void Attach() override;
        virtual void Detach() override;
        virtual void update() override;
        virtual void render() override = 0;
    };
}
