#pragma once

#include <string>

#include "../Scene.hpp"

namespace dex
{
    void SerializeScene(const std::string& file_location, const Scene& scene);

    Scene DeserializeScene(const std::string& file_location);
}
