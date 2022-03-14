#pragma once

#include <dex/Dexlite.hpp>
#include <imgui/imgui.h>
#include <ImGuizmo.h>
#include "../../../CurrentScene/CurrentScene.hpp"

namespace dex
{
    class ViewportPanel
    {
    public:
        ViewportPanel(dex::Window* window, Renderer* renderer, CurrentScene* current_scene);

        void update();
        void render();
    private:
        dex::Window* m_Window;
        Renderer* m_Renderer = nullptr;
    private:
        CurrentScene* m_CurrentScene;
        Framebuffer m_Framebuffer;

        glm::vec2 m_ViewportBounds[2] = { glm::vec2(0, 0), glm::vec2(0, 0) };

        ImGuizmo::OPERATION m_ActiveGuizmoOperation = ImGuizmo::OPERATION::TRANSLATE;
    };
}
