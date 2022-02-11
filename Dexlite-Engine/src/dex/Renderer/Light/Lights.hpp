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
                return Enabled != other.Enabled || Color != other.Color;
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
            Directional(bool enabled, const glm::vec3& color)
                : Base(enabled, color)
            {}

            inline const bool operator!=(const Directional& other) const
            {
                return Enabled != other.Enabled || Color != other.Color || Direction != other.Direction;
            }
        public:
            glm::vec3 Direction = { 0.0f, 0.0f, 0.0f };
        };

        struct Point : Base
        {
            Point() = default;
            Point(bool enabled, const glm::vec3& color, float constant, float linear, float quadratic)
                : Base(enabled, color), Constant(constant), Linear(linear), Quadratic(quadratic)
            {}

            // For vectors.
            inline const bool operator==(const Point& other) const
            {
                return
                    Enabled == other.Enabled &&
                    Color == other.Color &&
                    Position == other.Position &&
                    Constant == other.Constant &&
                    Linear == other.Linear &&
                    Quadratic == other.Quadratic
                ;
            }

            inline const bool operator!=(const Point& other) const
            {
                return
                    Enabled != other.Enabled ||
                    Color != other.Color ||
                    Position != other.Position || 
                    Constant != other.Constant || 
                    Linear != other.Linear || 
                    Quadratic != other.Quadratic;
            }
        public:
            glm::vec3 Position = { 0.0f, 0.0f, 0.0f };

            float Constant = 1.0f;
            float Linear = .35f;
            float Quadratic = .44f;
        };
    }
}
