#pragma once

#include "../../Renderer/Camera/OrthographicCamera.hpp"

namespace nim
{
	struct OrthoCamera
	{
		OrthoCamera(glm::vec4 bounds, glm::vec3 position, glm::vec3 rotation)
			: m_Camera(bounds, position, rotation)
		{}

		OrthographicCamera m_Camera;
	};
}
