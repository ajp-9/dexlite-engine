#include "FileDialog.hpp"

#include <imgui/imgui.h>

namespace dex
{
    bool BasicFileDialog(const char* label, std::filesystem::path* selected_file, bool* open, char* open_or_save);

    bool SaveFileDialog(const char* label, std::filesystem::path* save_file, bool* open)
    {
        return false;
    }

    bool OpenFileDialog(const char* label, std::filesystem::path* selected_file, bool* open)
    {
        return BasicFileDialog(label, selected_file, open, "Open File:");
    }

    bool BasicFileDialog(const char* label, std::filesystem::path* selected_file, bool* open, char* open_or_save)
    {
        static std::string selected;
        bool was_selected = false;

        ImVec2 center = ImGui::GetMainViewport()->GetCenter();
        ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

        if (ImGui::BeginPopupModal(label, open))
        {
            static auto& path_offset = std::filesystem::path();
            bool doubleclicked = false;

            ImGui::Text("Current Path: %s", path_offset.u8string().c_str());

            ImGui::Separator();

            ImGui::Text("Search:"); ImGui::SameLine();

            static std::string search_buffer_str;
            char buffer[0xFF];
            std::strncpy(buffer, search_buffer_str.c_str(), sizeof(buffer));

            ImGui::InputText("##Filter Text", buffer, sizeof(buffer));

            search_buffer_str = buffer;
            ImGui::GetStateStorage();

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

                    ImGui::TableNextRow();
                    ImGui::TableNextColumn();
                    if (u8_filename_str.find(search_buffer_str) != std::string::npos)
                    {
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

                //ImGui::TableSetColumnIndex(2);
                ImGui::SameLine();
                if ((ImGui::Button("Open") || doubleclicked) && !selected.empty())
                {
                    *selected_file = path_offset / selected;
                    was_selected = true;
                    selected = "";
                    ImGui::CloseCurrentPopup();
                }

                ImGui::TableSetColumnIndex(2);

                ImGui::Text("Filter:");
                ImGui::SameLine();
                //ImGui::TableSetColumnIndex(3);
                if (ImGui::BeginCombo("##wat", "tttt"))
                {
                    ImGui::Selectable("ioiiii");
                    ImGui::EndCombo();
                }

                ImGui::EndTable();
            }

            if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_Escape)))
            {
                selected = "";
                ImGui::CloseCurrentPopup();
            }

            ImGui::EndPopup();
        }
        else
        {
            selected = "";
        }

        return was_selected;
    }
}
