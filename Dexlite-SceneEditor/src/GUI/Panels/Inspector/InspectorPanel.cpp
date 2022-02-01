#include "InspectorPanel.hpp"

#include <imgui/imgui.h>
#include <dex/Renderer/ImGuiExtra/ImGuiExtra.hpp>

namespace dex
{
    InspectorPanel::InspectorPanel(CurrentScene* current_scene)
        : m_CurrentScene(current_scene)
    {
    }

    template <typename T>
    using UIFunction = void(T& t);

    template <typename T>
    static void renderComponent(const char* name, Entity& entity, UIFunction<T>* func)
    {
        bool opened = (ImGui::CollapsingHeader(name, ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth));
        
        if (opened)
        {
            func(entity.getComponent<T>());
        }
    }

    void InspectorPanel::render()
    {
        ImGui::Begin("Inspector", (bool*)0, ImGuiWindowFlags_NoCollapse);

        Entity selected_entity = m_CurrentScene->SelectedEntity;

        if (selected_entity.isValid())
        {
            auto& tag = selected_entity.getComponent<Component::Tag>().m_Tag;

            char buffer[0xFF];

            //std::memset(buffer, 0, sizeof(buffer));
            std::strncpy(buffer, tag.c_str(), sizeof(buffer));

            if (ImGui::InputText("##Tag", buffer, sizeof(buffer)))
            {
                tag = std::string(buffer);
            }

            ImGui::SameLine();

            ImGui::TextDisabled("ID: %u", selected_entity.getHandle());

            ImGui::Separator();

            renderComponent<Component::Transform>("Transform", selected_entity, [](Component::Transform& component)
            {
                ImGuiStyle& style = ImGui::GetStyle();

                if (ImGui::BeginTable("ttt", 2))
                {
                    ImGui::TableSetupColumn(nullptr, ImGuiTableColumnFlags_WidthFixed);
                    ImGui::TableSetupColumn(nullptr, ImGuiTableColumnFlags_WidthStretch);

                    {
                        ImGui::TableNextRow();

                        {
                            ImGui::TableSetColumnIndex(0);
                            ImGui::Text("Translation: ");
                        }

                        {
                            ImGui::TableSetColumnIndex(1);

                            ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x);
                            ImGui::DragFloat3("##T", &component.m_Position.x, .025);
                            ImGui::PopItemWidth();
                        }
                    }

                    {
                        ImGui::TableNextRow();

                        {
                            ImGui::TableSetColumnIndex(0);

                            ImGui::Text("Rotation: ");
                        }

                        {
                            ImGui::TableSetColumnIndex(1);

                            glm::vec3 rotation = component.getOrientationDegrees();
                            float rot_f3[3] = { rotation.x, rotation.y, rotation.z };
                            
                            ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x);
                            if (ImGui::DragFloat3("##R", &rot_f3[0], .025, -360.0f, 360.0f))
                            {
                                if (ImGui::IsMouseDragging(ImGuiMouseButton_Left) && !ImGui::dex::IsTextInputActive())
                                    component.rotateByEuler(glm::radians(rotation - glm::vec3(rot_f3[0], rot_f3[1], rot_f3[2])));

                                if (ImGui::IsItemDeactivated())
                                    component.setOrientationEuler(glm::radians(glm::vec3(rot_f3[0], rot_f3[1], rot_f3[2])));
                            }
                            ImGui::PopItemWidth();
                        }
                    }

                    {
                        ImGui::TableNextRow();

                        {
                            ImGui::TableSetColumnIndex(0);

                            ImGui::Text("Scale: ");
                        }

                        {
                            ImGui::TableSetColumnIndex(1);

                            ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x);
                            ImGui::DragFloat3("##S", &component.m_Scale.x, .025);
                            ImGui::PopItemWidth();
                        }
                    }

                    ImGui::EndTable();
                }
            });

            //ImGui::PushItemWidth(-(ImGui::GetWindowContentRegionWidth() - ImGui::CalcItemWidth()));

            ImGui::Separator();
            
            if (ImGui::BeginTable("cmp", 3))
            {
                ImGui::TableSetupColumn(nullptr, ImGuiTableColumnFlags_WidthStretch);
                ImGui::TableSetupColumn(nullptr, ImGuiTableColumnFlags_WidthFixed);
                ImGui::TableSetupColumn(nullptr, ImGuiTableColumnFlags_WidthStretch);

                ImGui::TableNextRow();

                ImGui::TableSetColumnIndex(0);
                ImGui::TableSetColumnIndex(1);
                if (ImGui::Button("Add Component"))
                    ImGui::OpenPopup("AddComponent");

                ImGui::TableSetColumnIndex(2);

                ImGui::EndTable();
            }
            

            //ImGui::PopItemWidth();
        }



        ImGui::End();
    }
}
