#pragma once

#include <vector>
#include <filesystem>

namespace dex
{
    bool BasicFileDialog(
        const char* btn_label,
        std::filesystem::path* selected_file,
        bool* open,
        const std::vector<std::filesystem::path>& filtered_extensions);
}
