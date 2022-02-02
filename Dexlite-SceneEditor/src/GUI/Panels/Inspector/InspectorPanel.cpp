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
        if (entity.hasComponent<T>())
        {
            bool opened = (ImGui::CollapsingHeader(name, ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth));

            if (opened)
            {
                func(entity.getComponent<T>());
            }
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

                if (ImGui::BeginTable("Component::Transform", 2))
                {
                    ImGui::TableSetupColumn(nullptr, ImGuiTableColumnFlags_WidthFixed);
                    ImGui::TableSetupColumn(nullptr, ImGuiTableColumnFlags_WidthStretch);

                    {
                        ImGui::TableNextRow();

                        {
                            ImGui::TableSetColumnIndex(0);
                            ImGui::dex::SetNextItemEvenSpacing();
                            ImGui::Text("Translation: ");
                        }

                        {
                            ImGui::TableSetColumnIndex(1);

                            ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x);
                            ImGui::DragFloat3("##Transformation", &component.m_Position.x, .025);
                            ImGui::PopItemWidth();
                        }
                    }

                    {
                        ImGui::TableNextRow();

                        {
                            ImGui::TableSetColumnIndex(0);
                            ImGui::dex::SetNextItemEvenSpacing();
                            ImGui::Text("Rotation: ");
                        }

                        {
                            ImGui::TableSetColumnIndex(1);

                            glm::vec3 rotation = component.getOrientationDegrees();
                            float rot_f3[3] = { rotation.x, rotation.y, rotation.z };
                            
                            ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x);
                            if (ImGui::DragFloat3("##Rotation", &rot_f3[0], .075, -360.0f, 360.0f))
                            {
                                if (ImGui::IsMouseDragging(ImGuiMouseButton_Left) && !ImGui::dex::IsTextInputActive())
                                    component.rotateByEuler(glm::radians(glm::vec3(rot_f3[0], rot_f3[1], rot_f3[2]) - rotation));

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
                            ImGui::dex::SetNextItemEvenSpacing();
                            ImGui::Text("Scale: ");
                        }

                        {
                            ImGui::TableSetColumnIndex(1);

                            ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x);
                            ImGui::DragFloat3("##Scale", &component.m_Scale.x, .025);
                            ImGui::PopItemWidth();
                        }
                    }

                    ImGui::EndTable();
                }
            });

            renderComponent<Component::Camera>("Camera", selected_entity, [](Component::Camera& component)
            {
                ImGui::Text("Enabled: ");
                ImGui::SameLine();
                ImGui::Checkbox("##Camera::IsEnabled", &component.IsEnabled);

                ImGui::dex::SetNextItemEvenSpacing();
                ImGui::Text("Projection: ");
                ImGui::SameLine();
                if (ImGui::BeginCombo("##Projection", component.m_Type == Component::Camera::CameraType::ORTHOGRAPHIC ? "Orthographic" : "Perspective"))
                {
                    if (ImGui::Selectable("Orthographic", component.m_Type == Component::Camera::CameraType::ORTHOGRAPHIC))
                    {
                        component.m_Type = Component::Camera::CameraType::ORTHOGRAPHIC;
                    }

                    if (ImGui::Selectable("Perspective", component.m_Type == Component::Camera::CameraType::PERSPECTIVE))
                    {
                        component.m_Type = Component::Camera::CameraType::PERSPECTIVE;
                    }

                    ImGui::EndCombo();
                }

                ImGui::Separator();

                if (component.m_Type == Component::Camera::CameraType::ORTHOGRAPHIC)
                {
                    ImGui::DragFloat("Size", &component.m_Ortho_Size);
                }

                if (component.m_Type == Component::Camera::CameraType::PERSPECTIVE)
                {
                    ImGui::DragFloat("FOV", &component.m_Persp_FOV, 0.1f, 2.5f, 125.0f);
                }

                ImGui::DragFloat("Near", &component.m_Near, .0005, 0.0001f, 2.5f);
                ImGui::DragFloat("Far", &component.m_Far, .25, 0.0f);

            });

            renderComponent<Component::Model>("Model", selected_entity, [](Component::Model& component)
            {
                ImGui::Text("Enabled: ");
                ImGui::SameLine();
                ImGui::Checkbox("##Model::Enabled", &component.Enabled);
            });

            renderComponent<Component::Light::Ambient>("Ambient Light", selected_entity, [](Component::Light::Ambient& ambient)
            {
                ImGui::Text("Enabled: ");
                ImGui::SameLine();
                ImGui::Checkbox("##Ambient::Enabled", &ambient.Enabled);

                ImGui::dex::SetNextItemEvenSpacing();
                ImGui::Text("Color: ");
                ImGui::SameLine();

                ImGui::ColorEdit3("##Ambient::Color", &ambient.Color.x);
            });

            renderComponent<Component::Light::Directional>("Directional Light", selected_entity, [](Component::Light::Directional& directional)
            {
                ImGui::Text("Enabled: ");
                ImGui::SameLine();
                ImGui::Checkbox("##Directional::Enabled", &directional.Enabled);

                ImGui::dex::SetNextItemEvenSpacing();
                ImGui::Text("Color: ");
                ImGui::SameLine();

                ImGui::ColorEdit3("##Directional::Color", &directional.Color.x);
            });

            renderComponent<Component::Light::Point>("Point Light", selected_entity, [](Component::Light::Point& point)
            {
                ImGui::Text("Enabled: ");
                ImGui::SameLine();
                ImGui::Checkbox("##Point::Enabled", &point.Enabled);

                ImGui::dex::SetNextItemEvenSpacing();
                ImGui::Text("Color: ");
                ImGui::SameLine();

                ImGui::ColorEdit3("##Point::Color", &point.Color.x);
            });

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
        }

        ImGui::End();
    }
}
