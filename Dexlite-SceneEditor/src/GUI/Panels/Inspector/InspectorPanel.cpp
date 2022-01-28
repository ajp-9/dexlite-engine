#include "InspectorPanel.hpp"

#include <imgui/imgui.h>

namespace dex
{
    InspectorPanel::InspectorPanel(CurrentScene* current_scene)
        : m_CurrentScene(current_scene)
    {
    }

    void InspectorPanel::render()
    {
        ImGui::Begin("Inspector", (bool*)0, ImGuiWindowFlags_NoCollapse);

        Entity selected_entity = m_CurrentScene->SelectedEntity;

        if (selected_entity.isValid())
        {
            if (selected_entity.hasComponent<Component::Tag>())
            {
                auto& tag = selected_entity.getComponent<Component::Tag>().m_Tag;

                char buffer[0xFF];

                //std::memset(buffer, 0, sizeof(buffer));
                std::strncpy(buffer, tag.c_str(), sizeof(buffer));

                if (ImGui::InputText("##Tag", buffer, sizeof(buffer)))
                {
                    tag = std::string(buffer);
                }
            }
        }

        ImGui::End();
    }
}
