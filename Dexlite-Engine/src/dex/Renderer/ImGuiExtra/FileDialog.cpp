#include "FileDialog.hpp"

#include <imgui/imgui.h>

#include "../../Util/Logging.hpp"

namespace dex
{
    bool BasicFileDialog(
        const char* label,
        const char* btn_label,
        std::filesystem::path* selected_file,
        bool* open,
        bool* closed,
        const std::vector<std::filesystem::path>& filtered_extensions)
    {
        static std::string selected;
        static std::filesystem::path current_filtered_extension;

        bool was_selected = false;

        ImVec2 center = ImGui::GetMainViewport()->GetCenter();
        ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

        if (ImGui::BeginPopupModal(label, open))
        {
            // When the modal is created.
            if (ImGui::IsWindowAppearing())
            {
                if (!filtered_extensions.empty())
                    current_filtered_extension = filtered_extensions.at(0);
                else
                    DEX_LOG_ERROR("<dex::BasicFileDialog()>: Filtered extensions can't be empty");

                selected = "";
            }

            static auto path_offset = std::filesystem::path();
            bool doubleclicked = false;

            ImGui::Text("Current Path: %s", path_offset.u8string().c_str());

            ImGui::Separator();

            ImGui::Text("Search:"); ImGui::SameLine();

            static std::string search_buffer_str;
            char buffer[0xFF];
            std::strncpy(buffer, search_buffer_str.c_str(), sizeof(buffer));

            ImGui::InputText("##Filter Text", buffer, sizeof(buffer));

            search_buffer_str = buffer;

            if (ImGui::BeginTable("table", 1, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_ScrollY, ImVec2(0.0f, ImGui::GetWindowSize().y - 110)))
            {
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                if (ImGui::Selectable("...", false))
                {
                    if (!path_offset.empty())
                        path_offset = path_offset.parent_path();

                    selected = "";
                }

                for (const auto& file : std::filesystem::directory_iterator(std::filesystem::current_path() / path_offset))
                {
                    auto u8_filename_str = file.path().filename().u8string();

                    if (file.is_directory() || current_filtered_extension == "None" || std::filesystem::path(file).extension().u8string() == current_filtered_extension)
                    {
                        if (u8_filename_str.find(search_buffer_str) != std::string::npos)
                        {
                            ImGui::TableNextRow();
                            ImGui::TableNextColumn();

                            if (ImGui::Selectable(u8_filename_str.c_str(), (selected == u8_filename_str) ? true : false, ImGuiSelectableFlags_AllowDoubleClick))
                            {
                                selected = u8_filename_str;

                                if (file.is_directory())
                                {
                                    path_offset /= u8_filename_str;
                                    selected = "";
                                }

                                if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
                                {
                                    doubleclicked = true;
                                }
                            }
                        }
                    }
                }

                ImGui::EndTable();
            }

            if (ImGui::BeginTable("cmp1", 3))
            {
                ImGui::TableSetupColumn(nullptr, ImGuiTableColumnFlags_WidthFixed);
                ImGui::TableSetupColumn(nullptr, ImGuiTableColumnFlags_WidthStretch);
                //ImGui::TableSetupColumn(nullptr, ImGuiTableColumnFlags_WidthFixed);
                //ImGui::TableSetupColumn(nullptr, ImGuiTableColumnFlags_WidthFixed);
                ImGui::TableSetupColumn(nullptr, ImGuiTableColumnFlags_WidthFixed);

                ImGui::TableNextRow();

                ImGui::TableSetColumnIndex(0);

                ImGui::Text("File:");
                ImGui::SameLine();

                static char b[0xFF];
                std::strncpy(b, selected.c_str(), sizeof(b));

                ImGui::TableSetColumnIndex(1);

                ImGui::InputText("##File Selected", b, sizeof(b));

                selected = b;

                //ImGui::TableSetColumnIndex(2);
                ImGui::SameLine();
                if ((ImGui::Button(btn_label) || doubleclicked) && !selected.empty())
                {
                    *selected_file = path_offset / selected;
                    was_selected = true;
                    selected = "";
                    if (closed != nullptr)
                        *closed = true;
                    ImGui::CloseCurrentPopup();
                }

                ImGui::TableSetColumnIndex(2);

                ImGui::Text("Filter:");
                ImGui::SameLine();
                //ImGui::TableSetColumnIndex(3);
                if (ImGui::BeginCombo("##ExtensionFilterCombo", current_filtered_extension.u8string().c_str()))
                {
                    for (const auto& filter : filtered_extensions)
                    {
                        if (ImGui::Selectable(filter.u8string().c_str(), current_filtered_extension == filter.u8string().c_str()))
                            current_filtered_extension = filter;
                    }

                    ImGui::EndCombo();
                }

                ImGui::EndTable();
            }

            if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_Escape)))
            {
                selected = "";
                if (closed != nullptr)
                    *closed = true;
                ImGui::CloseCurrentPopup();
            }

            ImGui::EndPopup();
        }

        return was_selected;
    }
}
