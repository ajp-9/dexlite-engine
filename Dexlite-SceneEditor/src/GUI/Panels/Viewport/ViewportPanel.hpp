#pragma once

#include <dex/Dexlite.hpp>

namespace dex
{
    class ViewportPanel
    {
    public:
        ViewportPanel();

        void render(Scene& scene);

        void setViewportCamera(std::shared_ptr<Entity> entity) { m_ViewportCamera = entity; }
    private:
        std::shared_ptr<Entity> m_ViewportCamera;

        Framebuffer m_Framebuffer;
    };
}