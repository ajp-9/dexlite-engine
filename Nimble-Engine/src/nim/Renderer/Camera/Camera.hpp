#pragma once

#include <glm/mat4x4.hpp>

namespace nim
{
	class Camera
	{
	public:
		Camera(const glm::mat4& projection)
			: m_ProjectionMatrix(projection)
		{}

		const glm::mat4& getProjectionMatrix() const { return m_ProjectionMatrix; }
	protected:
		glm::mat4 m_ProjectionMatrix;
	};
}
