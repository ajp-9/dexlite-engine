#include "InspectorPanel.hpp"

#include <filesystem>
#include <imgui/imgui.h>
#include <dex/Renderer/ImGuiExtra/ImGuiExtra.hpp>

#include "../../Dialog/FileDialog.hpp"

namespace dex
{
    InspectorPanel::InspectorPanel(dex::Window* window, dex::Renderer* renderer, CurrentScene* current_scene)
        : m_Window(window), m_Renderer(renderer), m_CurrentScene(current_scene)
    {
    }

    template <typename T>
    using UIFunction = void(T& t, Renderer* renderer);

    template <typename T>
    static void renderComponent(const char* name, Entity& entity, Renderer* renderer, UIFunction<T>* func)
    {
        if (entity.hasComponent<T>())
        {
            bool opened = (ImGui::CollapsingHeader(name, ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth));

            if (opened)
            {
                func(entity.getComponent<T>(), renderer);
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

            renderComponent<Component::Transform>("Transform", selected_entity, m_Renderer, [](Component::Transform& component, Renderer* renderer)
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

            renderComponent<Component::Camera>("Camera", selected_entity, m_Renderer, [](Component::Camera& component, Renderer* renderer)
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
            
            renderComponent<Component::Model>("Model", selected_entity, m_Renderer, [](Component::Model& component, Renderer* renderer)
            {
                ImGui::Text("Enabled: ");
                ImGui::SameLine();
                ImGui::Checkbox("##Model::Enabled", &component.Enabled);

                char buffer[0xFF];
                std::strcpy(buffer, component.FileLocation.u8string().c_str());

                if (ImGui::InputText("##Model::FileLocation", buffer, sizeof(buffer)))
                {
                    component.FileLocation = buffer;
                }

                ImGui::SameLine();

                static bool open = false;
                if (ImGui::Button("Choose File"))
                {
                    ImGui::OpenPopup("Choose File");
                    open = true;
                }

                std::filesystem::path path;
                if (OpenFileDialog(&path, &open, { ".glb", "None" }))
                {
                    component = Component::Model(LoadGLTF(path.u8string(), renderer->ShaderManager.getShaderDerived<Shader::Default3D>(Shader::Type::DEFAULT_3D)));
                }
            });

            renderComponent<Component::Light::Ambient>("Ambient Light", selected_entity, m_Renderer, [](Component::Light::Ambient& ambient, Renderer* renderer)
            {
                ImGui::Text("Enabled: ");
                ImGui::SameLine();
                ImGui::Checkbox("##Ambient::Enabled", &ambient.Enabled);

                ImGui::dex::SetNextItemEvenSpacing();
                ImGui::Text("Color: ");
                ImGui::SameLine();

                ImGui::ColorEdit3("##Ambient::Color", &ambient.Color.x);
            });

            renderComponent<Component::Light::Directional>("Directional Light", selected_entity, m_Renderer, [](Component::Light::Directional& directional, Renderer* renderer)
            {
                ImGui::Text("Enabled: ");
                ImGui::SameLine();
                ImGui::Checkbox("##Directional::Enabled", &directional.Enabled);

                ImGui::dex::SetNextItemEvenSpacing();
                ImGui::Text("Color: ");
                ImGui::SameLine();

                ImGui::ColorEdit3("##Directional::Color", &directional.Color.x);
            });

            renderComponent<Component::Light::Point>("Point Light", selected_entity, m_Renderer, [](Component::Light::Point& point, Renderer* renderer)
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
                {
                    ImGui::OpenPopup("Add Component##Popup");
                }

                if (ImGui::BeginPopup("Add Component##Popup"))
                {
                    if (ImGui::MenuItem("Camera", NULL, false, !selected_entity.hasComponent<Component::Camera>()))
                    {
                        if (!selected_entity.hasComponent<Component::Camera>())
                            selected_entity.addComponent<Component::Camera>();

                        ImGui::CloseCurrentPopup();
                    }

                    if (ImGui::MenuItem("Model", NULL, false, !selected_entity.hasComponent<Component::Model>()))
                    {
                        if (!selected_entity.hasComponent<Component::Model>())
                            selected_entity.addComponent<Component::Model>();

                        ImGui::CloseCurrentPopup();
                    }

                    if (ImGui::BeginMenu("Light"))
                    {
                        if (ImGui::MenuItem("Ambient Light", NULL, false, !selected_entity.hasComponent<Component::Light::Ambient>()))
                        {
                            if (!selected_entity.hasComponent<Component::Light::Ambient>())
                                selected_entity.addComponent<Component::Light::Ambient>();

                            ImGui::CloseCurrentPopup();
                        }

                        if (ImGui::MenuItem("Directional Light", NULL, false, !selected_entity.hasComponent<Component::Light::Directional>()))
                        {
                            if (!selected_entity.hasComponent<Component::Light::Directional>())
                                selected_entity.addComponent<Component::Light::Directional>();

                            ImGui::CloseCurrentPopup();
                        }

                        if (ImGui::MenuItem("Point Light", NULL, false, !selected_entity.hasComponent<Component::Light::Point>()))
                        {
                            if (!selected_entity.hasComponent<Component::Light::Point>())
                                selected_entity.addComponent<Component::Light::Point>();

                            ImGui::CloseCurrentPopup();
                        }

                        ImGui::EndMenu();
                    }

                    ImGui::EndPopup();
                    
                    m_Window->Input.stopMouseEvents();
                }

                ImGui::TableSetColumnIndex(2);

                ImGui::EndTable();
            }
        }

        ImGui::End();
    }
}
