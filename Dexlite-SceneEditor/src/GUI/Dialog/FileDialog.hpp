#pragma once

#include <filesystem>
#include <dex/Renderer/ImGuiExtra/FileDialog.hpp>

namespace dex
{
    inline bool SaveFileDialog(
        const char* label,
        std::filesystem::path* selected_file,
        bool* open,
        bool* closed = nullptr,
        const std::vector<std::filesystem::path>& filtered_extensions = { "None" })
    {
        return BasicFileDialog(label, "Save", selected_file, open, closed, filtered_extensions);
    }

    inline bool OpenFileDialog(
        const char* label,
        std::filesystem::path* selected_file,
        bool* open,
        bool* closed = nullptr,
        const std::vector<std::filesystem::path>& filtered_extensions = { "None" })
    {
        return BasicFileDialog(label, "Open", selected_file, open, closed, filtered_extensions);
    }
}
