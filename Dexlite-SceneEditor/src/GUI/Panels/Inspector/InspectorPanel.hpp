#pragma once

#include "../../../CurrentScene/CurrentScene.hpp"
#include <dex/Dexlite.hpp>

namespace dex
{
    class InspectorPanel
    {
    public:
        InspectorPanel(dex::Window* window, dex::Renderer* renderer, CurrentScene* current_scene);

        void render();
    private:
        Window* m_Window = nullptr;
        Renderer* m_Renderer = nullptr;
    private:
        CurrentScene* m_CurrentScene;
    };
}
