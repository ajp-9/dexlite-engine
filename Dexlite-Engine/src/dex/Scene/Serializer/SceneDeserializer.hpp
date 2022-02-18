#pragma once

#include "../Scene.hpp"
#include <filesystem>

#include "../../Renderer/Shader/3D/ShaderDefault3D.hpp"

namespace dex
{
    Scene DeserializeScene(const std::filesystem::path& file_location, const std::shared_ptr<Shader::Default3D>& shader_default_3d);
}
