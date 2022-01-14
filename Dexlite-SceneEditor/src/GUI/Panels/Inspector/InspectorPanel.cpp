#include "InspectorPanel.hpp"

#include <imgui/imgui.h>

namespace dex
{
    void InspectorPanel::render()
    {
        ImGui::Begin("Inspector", (bool*)0, ImGuiWindowFlags_NoCollapse);
        ImGui::End();
    }
}
