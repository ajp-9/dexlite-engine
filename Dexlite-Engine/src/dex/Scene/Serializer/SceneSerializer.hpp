#pragma once

#include <filesystem>

#include "../Scene.hpp"

namespace dex
{
    void SerializeScene(const std::filesystem::path& file_location, const Scene& scene);
}
