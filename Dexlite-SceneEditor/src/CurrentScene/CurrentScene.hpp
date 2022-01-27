#pragma once

#include <dex/Dexlite.hpp>

namespace dex
{
    class CurrentScene
    {
        Window* Window = nullptr;
        Renderer* Renderer = nullptr;
    public:
        CurrentScene(dex::Window* window, dex::Renderer* renderer);

        void update(const float delta_time);
        void render(const glm::vec2& viewport_size);
    public:
        Scene Scene;

        Entity SelectedEntity = { entt::null, &Scene };

        //dex::Entity m_ViewportCamera = { &Scene, "Viewport Camera" };
    private:
        dex::Entity m_Player = { &Scene, "Player" };
        dex::Entity m_Head = { &Scene, "Head" };

        dex::Entity m_XYZ = { &Scene, "XYZ" };
        dex::Entity m_Warlock = { &Scene, "Warlock" };
        dex::Entity m_Valdore = { &Scene, "Valdore" };
        dex::Entity m_LightSphere = { &Scene, "Light Sphere" };
        dex::Entity m_Triangle = { &Scene, "Triangle" };
    };
}
