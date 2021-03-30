#pragma once

#include "Camera.hpp"

namespace nim
{
	class OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera(glm::vec4 bounds, glm::vec3 position, glm::vec3 rotation);
	private:
		void calculateViewMatrix();
	};
}
