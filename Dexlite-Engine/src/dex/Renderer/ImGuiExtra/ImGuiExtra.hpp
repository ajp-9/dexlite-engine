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

        void SetNextItemEvenSpacing()
        {
            ImGui::GetCurrentWindow()->DC.CursorPos.y += ImGui::GetStyle().ItemSpacing.y * 0.5f;
        }
    }
}
