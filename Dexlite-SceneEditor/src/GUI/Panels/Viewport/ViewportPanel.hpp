#pragma once

#include <dex/Dexlite.hpp>
#include "../../../CurrentScene/CurrentScene.hpp"

namespace dex
{
    class ViewportPanel
    {
    public:
        ViewportPanel();

        void render(CurrentScene& current_scene, Renderer& renderer);
    private:
        Framebuffer m_Framebuffer;
    };
}
