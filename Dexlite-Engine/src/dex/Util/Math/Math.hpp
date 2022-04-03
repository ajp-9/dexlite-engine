#pragma once

#include <glm/mat4x4.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/quaternion.hpp>

namespace dex
{
    namespace Math
    {
        void decomposeTransform(const glm::mat4& matrix, glm::vec3* translation = nullptr, glm::quat* orientation = nullptr, glm::vec3* scale = nullptr);
    }
}
