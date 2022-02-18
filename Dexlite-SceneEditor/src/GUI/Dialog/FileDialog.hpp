#pragma once

#include <filesystem>

namespace dex
{
    bool SaveFileDialog(const char* label, std::filesystem::path* save_file, bool* open = nullptr);
    bool OpenFileDialog(const char* label, std::filesystem::path* selected_file, bool* open = nullptr);
}
