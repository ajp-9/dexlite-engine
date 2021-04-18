#pragma once

#include "../../../Renderer/Camera/PerspectiveCamera.hpp"

namespace dex
{
	namespace Component
	{
		struct PerspCamera
		{
			PerspCamera(bool isMainCamera, PerspectiveCamera& camera)
				: m_IsMainCamera(isMainCamera), m_Camera(camera)
			{}

			PerspectiveCamera m_Camera;
			bool m_IsMainCamera = false;
		};
	}
}
