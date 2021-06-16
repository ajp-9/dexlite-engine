#pragma once

#include "../../Renderer/Camera/Camera.hpp"

namespace dex
{
    namespace Component
    {
        struct Camera : dex::Camera
        {
            Camera(bool isMain = true)
            {
                m_isMain = isMain;
            }

            bool m_isMain = false;
        };
    }
}
