#pragma once

#include <glm/vec4.hpp>

namespace nim
{
	namespace gl
	{
		class OpenGL_API
		{
			OpenGL_API();

			void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

			void setClearColor(const glm::vec4& color);
			void clear();
		};
	}
}
