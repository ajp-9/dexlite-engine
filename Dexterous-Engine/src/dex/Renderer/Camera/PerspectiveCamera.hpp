#pragma once

#include "CameraBase.hpp"
#include "../../Util/Typedefs.hpp"

namespace dex
{
    namespace Camera
    {
        class Perspective : public Base
        {
        public:
            // Bounds are: near and far.
            Perspective(float32 fov, glm::uvec2 screenDimensions, glm::vec2 bounds, glm::vec3 position = glm::vec3(0), glm::vec3 rotation = glm::vec3(0));
        private:
            void calculateViewMatrix();
        private:
            float32 fov = 90;
        };
    }
}
