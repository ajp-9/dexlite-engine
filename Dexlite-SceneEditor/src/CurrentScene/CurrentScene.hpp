#pragma once

#include <filesystem>
#include <dex/Dexlite.hpp>

namespace dex
{
    class CurrentScene
    {
        Window* Window = nullptr;
        Renderer* Renderer = nullptr;
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
    public:
        Scene Scene;
        std::filesystem::path Path;

        Entity SelectedEntity = { entt::null, &Scene };

        dex::Entity m_ViewportCamera = { &Scene, "Viewport Camera", false };
    };
}
