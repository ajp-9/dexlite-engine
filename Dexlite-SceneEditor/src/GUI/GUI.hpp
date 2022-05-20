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
    public:
        GUI(dex::Window* window, dex::Renderer* renderer, CurrentScene* current_scene, bool* running);

        void update(const float delta_time);
        void render();
    private:
        void renderSceneController();
        void setColorsAndStyle();
    private:
        Window* m_Window = nullptr;
        Renderer* m_Renderer = nullptr;
    private:
        CurrentScene* m_CurrentScene = nullptr;
        bool* m_Running = nullptr;
        
        SceneHierarchyPanel m_SceneHierarchyPanel;
        ViewportPanel m_ViewportPanel;
        InspectorPanel m_InspectorPanel;
    };
}
