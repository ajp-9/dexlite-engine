#pragma once

#include "Camera.hpp"

namespace dex
{
	class PerspectiveCamera : public Camera
	{
	public:
		// Bounds are: near and far.
		PerspectiveCamera(float fov, glm::uvec2 screenDimensions, glm::vec2 bounds, glm::vec3 position = glm::vec3(0), glm::vec3 rotation = glm::vec3(0));
	private:
		void calculateViewMatrix();
	private:
		float fov = 90;
	};
}
