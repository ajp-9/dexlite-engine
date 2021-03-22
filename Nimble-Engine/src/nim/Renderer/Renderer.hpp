#pragma once

#include <glm/vec4.hpp>

namespace nim
{
	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void update();

		static void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

		static void setClearColor(const glm::vec4& color);
		static void clear();
	};
}
