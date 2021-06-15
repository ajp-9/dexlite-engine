#pragma once

#include "../../../Renderer/Camera/OrthographicCamera.hpp"

namespace dex
{
    namespace Component
    {
        struct OrthographicCamera
        {
            OrthographicCamera(bool isMainCamera, Camera::Orthographic& camera)
                : m_IsMainCamera(isMainCamera), m_Camera(camera)
            {}

            Camera::Orthographic m_Camera;
            bool m_IsMainCamera = false;
        };
    }
}
