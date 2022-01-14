#include "SceneHierarchyPanel.hpp"

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include <string>
#include <dex/Util/Logging.hpp>
#include <dex/Dexlite.hpp>

namespace dex
{
    void SceneHierarchyPanel::render(Scene& scene)
    {
        ImGui::Begin("Scene Hierarchy", (bool*)0, ImGuiWindowFlags_NoCollapse);

        ImGui::End();
    }
}
