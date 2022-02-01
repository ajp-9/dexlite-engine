#pragma once

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

namespace ImGui
{
    namespace dex
    {
        bool IsTextInputActive()
        {
            return ImGui::TempInputIsActive(ImGui::GetCurrentWindow()->DC.LastItemId);
        }
    }
}
