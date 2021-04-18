#pragma once

#include "../../../Renderer/Camera/OrthographicCamera.hpp"

namespace dex
{
	namespace Component
	{
		struct OrthoCamera
		{
			OrthoCamera(bool isMainCamera, OrthographicCamera& camera)
				: m_IsMainCamera(isMainCamera), m_Camera(camera)
			{}

			OrthographicCamera m_Camera;
			bool m_IsMainCamera = false;
		};
	}
}
