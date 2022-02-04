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

        glm::vec2 m_ViewportBounds[2] = { glm::vec2(0, 0), glm::vec2(0, 0) };
    };
}
