#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include <glm/vec3.hpp>

namespace dex
{
    struct BasicTransform
    {
        glm::vec3 Position;
        glm::quat Orientation;
    };
}
