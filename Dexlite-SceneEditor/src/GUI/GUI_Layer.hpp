#pragma once

#include <dex/Dexlite.hpp>

#include "Panels/SceneHierarchy/SceneHierarchyPanel.hpp"
#include "Panels/Viewport/ViewportPanel.hpp"
#include "Panels/Inspector/InspectorPanel.hpp"

namespace dex
{
    class GUI_Layer : public dex::Layer::Base
    {
    public:
        GUI_Layer(const std::shared_ptr<Scene>& scene, std::shared_ptr<Entity> entity)
            : m_CurrentScene(scene), m_ViewportCamera(entity)
        {
            m_ViewportPanel.setViewportCamera(entity);
        }
    private:
        virtual void Attach();
        virtual void Detach();

        virtual void update();
        virtual void render();
    public:
        void setScene(const std::shared_ptr<Scene>& scene) { m_CurrentScene = scene; }
        void setViewportCamera(std::shared_ptr<Entity> entity) { m_ViewportCamera = entity; m_ViewportPanel.setViewportCamera(entity); }
    private:
        void setColorsAndStyle();
    private:
        std::shared_ptr<dex::Scene> m_CurrentScene;
        std::shared_ptr<Entity> m_ViewportCamera;

        SceneHierarchyPanel m_SceneHierarchyPanel;
        ViewportPanel m_ViewportPanel;
        InspectorPanel m_InspectorPanel;


        dex::Entity m_Player = { &*m_CurrentScene, "Player" };
        dex::Entity m_Head = { &*m_CurrentScene, "Head" };

        dex::Entity m_XYZ = { &*m_CurrentScene, "XYZ" };
        dex::Entity m_Warlock = { &*m_CurrentScene, "Warlock" };
        dex::Entity m_Valdore = { &*m_CurrentScene, "Valdore" };
        dex::Entity m_LightSphere = { &*m_CurrentScene, "Light Sphere" };
        dex::Entity m_Triangle = { &*m_CurrentScene, "Triangle" };

    };
}
