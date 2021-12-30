#pragma once

#include <glm/vec3.hpp>

namespace dex
{
    namespace Light
    {
        struct Base
        {
            Base() = default;
            Base(bool enabled, const glm::vec3& color)
                : Enabled(enabled), Color(color)
            {}

            inline const bool operator!=(const Base& other) const
            {
                return Color != other.Color;
            }

            bool Enabled = false;
            glm::vec3 Color = { 1.0f, 1.0f, 1.0f };
        };

        struct Ambient : Base
        {
            Ambient() = default;
            Ambient(bool enabled, const glm::vec3& color)
                : Base(enabled, color)
            {}
        };

        struct Directional : Base
        {
            Directional() = default;
            Directional(bool enabled, const glm::vec3& color, glm::vec3 direction)
                : Base(enabled, color), Direction(direction)
            {}

            inline const bool operator!=(const Directional& other) const
            {
                return Color != other.Color || Direction != other.Direction;
            }

            glm::vec3 Direction = { 0.0f, 0.0f, 0.0f };
        };

        struct Point : Base
        {
            Point() = default;
            Point(bool enabled, const glm::vec3& color, glm::vec3 position)
                : Base(enabled, color), Position(position)
            {}

            inline const bool operator!=(const Point& other) const
            {
                return Color != other.Color || Position != other.Position;
            }

            glm::vec3 Position = { 0.0f, 0.0f, 0.0f };
        };
    }
}
