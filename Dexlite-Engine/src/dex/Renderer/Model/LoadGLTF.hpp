#pragma once

#include <filesystem>

#include "../Mesh/Mesh.hpp"
#include "../Material/3D/MaterialDefault3D.hpp"
#include "Model.hpp"

namespace dex
{
    Model LoadGLTF(const std::filesystem::path& file_location, const std::shared_ptr<Shader::Default3D> shader_default_3d, bool enabled = true);
}
