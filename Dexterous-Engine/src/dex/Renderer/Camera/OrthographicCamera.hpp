#pragma once

#include "CameraBase.hpp"

namespace dex
{
	namespace Camera
	{
		class Orthographic : public Base
		{
		public:
			Orthographic(glm::vec4 bounds, glm::vec3 position, glm::vec3 rotation);
		private:
			void calculateViewMatrix();
		};
	}
}
