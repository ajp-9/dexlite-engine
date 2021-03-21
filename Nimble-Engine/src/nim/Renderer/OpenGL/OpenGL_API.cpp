#include "OpenGL_API.hpp"

#include <glad/glad.h>

namespace nim
{
	namespace gl
	{
		OpenGL_API::OpenGL_API()
		{

		}

		void OpenGL_API::setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			glViewport(x, y, width, height);
		}

		void OpenGL_API::setClearColor(const glm::vec4& color)
		{
			glClearColor(color.r, color.g, color.b, color.a);
		}

		void OpenGL_API::clear()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
	}
}
