#pragma once

#include "../Scene.hpp"
#include <filesystem>

#include "../../Physics/Physics.hpp"
#include "../../Renderer/Shader/3D/ShaderDefault3D.hpp"

namespace dex
{
    Scene DeserializeScene(const std::filesystem::path& file_location, Renderer* renderer, Physics* physics, const std::shared_ptr<Shader::Default3D>& shader_default_3d);
}
