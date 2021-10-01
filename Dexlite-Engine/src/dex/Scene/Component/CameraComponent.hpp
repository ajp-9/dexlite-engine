#pragma once

#include "../../Renderer/Camera/Camera.hpp"

namespace dex
{
    namespace Component
    {
        struct Camera : dex::Camera
        {
            // Only 1 camera can be enabled.
            Camera(bool isEnabled = true)
            {
                m_IsEnabled = isEnabled;
            }

            bool m_IsEnabled = false;
        };
    }
}
