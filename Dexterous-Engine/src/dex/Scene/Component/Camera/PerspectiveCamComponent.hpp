#pragma once

#include "../../../Renderer/Camera/PerspectiveCamera.hpp"

namespace dex
{
    namespace Component
    {
        struct PerspectiveCamera
        {
            PerspectiveCamera(bool isMainCamera, Camera::Perspective& camera)
                : m_IsMainCamera(isMainCamera), m_Camera(camera)
            {}

            Camera::Perspective m_Camera;
            bool m_IsMainCamera = false;
        };
    }
}
