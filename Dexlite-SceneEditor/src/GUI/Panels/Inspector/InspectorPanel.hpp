#pragma once

#include "../../../CurrentScene/CurrentScene.hpp"

namespace dex
{
    class InspectorPanel
    {
    public:
        InspectorPanel(CurrentScene* current_scene);

        void render();
    private:
        CurrentScene* m_CurrentScene;
    };
}
