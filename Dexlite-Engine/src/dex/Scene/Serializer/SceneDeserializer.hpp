#pragma once

#include "../Scene.hpp"

#include "../../Renderer/Shader/3D/ShaderDefault3D.hpp"

namespace dex
{
    Scene DeserializeScene(const std::string& file_location, const std::shared_ptr<Shader::Default3D>& shader_default_3d);
}
