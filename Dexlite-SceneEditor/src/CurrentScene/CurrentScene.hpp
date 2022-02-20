#pragma once

#include <filesystem>
#include <dex/Dexlite.hpp>

namespace dex
{
    class CurrentScene
    {
    public:
        CurrentScene(dex::Window* window, dex::Renderer* renderer);

        void New();
        void Save();
        void SaveAs(const std::filesystem::path& path);
        void Open(const std::filesystem::path& path);

        void update(const float delta_time);
        void render(const glm::vec2& viewport_size);
    private:
        void resetViewportCamera();
    private:
        Window* m_Window = nullptr;
        Renderer* m_Renderer = nullptr;
    public:
        dex::Scene Scene;
        std::filesystem::path Path;

        Entity SelectedEntity = { entt::null, &Scene };

        dex::Entity m_ViewportCamera = { &Scene, "Viewport Camera", false };
    };
}
