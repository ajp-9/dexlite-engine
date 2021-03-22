#pragma once

#include <glm/vec4.hpp>
#include <glm/vec2.hpp>

namespace nim
{
	class Renderer
	{
		static void Init(glm::uvec2 viewportDimensions);
		static void Shutdown();

		static void update();

		static void setViewport(uint32_t x, uint32_t y, glm::uvec2 dimensions);

		static void setClearColor(const glm::vec4& color);
		static void clear();

		friend class NimbleEngine;
		friend class Application;
	};
}
