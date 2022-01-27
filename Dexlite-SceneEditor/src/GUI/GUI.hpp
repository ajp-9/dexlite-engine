#pragma once

#include <dex/Dexlite.hpp>

#include "../CurrentScene/CurrentScene.hpp"

#include "Panels/SceneHierarchy/SceneHierarchyPanel.hpp"
#include "Panels/Viewport/ViewportPanel.hpp"
#include "Panels/Inspector/InspectorPanel.hpp"

namespace dex
{
    class GUI
    {
        //Window* Window = nullptr;
        Renderer* Renderer = nullptr;
    public:
        GUI(dex::Renderer* renderer, CurrentScene* current_scene);

        void update(const float delta_time);
        void render();
    private:
        void setColorsAndStyle();
    private:
        CurrentScene* m_CurrentScene = nullptr;
        
        SceneHierarchyPanel m_SceneHierarchyPanel;
        ViewportPanel m_ViewportPanel;
        InspectorPanel m_InspectorPanel;
    };
}
