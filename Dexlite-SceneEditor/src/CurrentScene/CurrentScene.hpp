#pragma once

#include <filesystem>
#include <dex/Dexlite.hpp>

namespace dex
{
    class CurrentScene
    {
    public:
        enum class State { EDIT, PLAY };
        enum class ViewportCameraState { NONE, PAN, FPS };
    public:
        CurrentScene(dex::Window* window, dex::Renderer* renderer, dex::Physics* physics);
        
        void New();
        void Save();
        void SaveAs(const std::filesystem::path& path);
        void Open(const std::filesystem::path& path);

        void update(const float delta_time);
        void render(const glm::vec2& viewport_size);
    private:
        void setupEntities();
    private:
        Window* m_Window = nullptr;
        Renderer* m_Renderer = nullptr;
        Physics* m_Physics = nullptr;

        dex::Entity m_EditorRoot;
    public:
        dex::Scene Scene;
        dex::CurrentScene::State State = { State::EDIT };
        std::filesystem::path Path;

        Entity SelectedEntity = { entt::null, &Scene };

        ViewportCameraState CurrentViewportState = ViewportCameraState::NONE;
    public:
        dex::Entity ViewportCameraBody;
        dex::Entity ViewportCameraHead;
    };
}
