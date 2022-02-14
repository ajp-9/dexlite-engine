#pragma once

#include <filesystem>

namespace dex
{
    bool FileDialog(const char* label, std::filesystem::path* selected_file, bool* open = nullptr);
}
