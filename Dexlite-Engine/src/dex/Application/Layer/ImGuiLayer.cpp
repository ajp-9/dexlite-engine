#include "ImGuiLayer.hpp"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "../../Renderer/ImGui/ImGuiAPI.hpp"
#include "../../Core/Engine.hpp"

namespace dex
{
    void ImGuiLayer::Attach() {}

    void ImGuiLayer::Detach() {}

    void ImGuiLayer::update()
    {
        if (ImGui::GetIO().WantCaptureKeyboard)
            Engine::Window.Input.stopKeyEvents();

        if (ImGui::GetIO().WantCaptureMouse)
            Engine::Window.Input.stopMouseEvents();
    }
}
