#pragma once

#include <filesystem>
#include <dex/Renderer/ImGuiExtra/FileDialog.hpp>

namespace dex
{
    inline bool SaveFileDialog(
        std::filesystem::path* selected_file,
        bool* open,
        const std::vector<std::filesystem::path>& filtered_extensions = { "None" })
    {
        return BasicFileDialog("Open", selected_file, open, filtered_extensions);
    }

    inline bool OpenFileDialog(
        std::filesystem::path* selected_file,
        bool* open,
        const std::vector<std::filesystem::path>& filtered_extensions = { "None" })
    {
        return BasicFileDialog("Open", selected_file, open, filtered_extensions);
    }
}
