#pragma once

#include "OpenGL/OpenGL_API.hpp"

namespace nim
{
	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		void update();

		void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

		void setClearColor(const glm::vec4& color);
		void clear();
	private:
	};
}
