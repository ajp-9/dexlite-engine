#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include <glm/vec3.hpp>

namespace dex
{
    struct Transform
    {
        glm::vec3 Position;
        glm::quat Rotation;
        glm::vec3 Scale;
    };
}
