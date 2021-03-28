#pragma once

#include <glm/vec4.hpp>

namespace nim
{
	class Renderer
	{
		static void Init(glm::uvec4 viewport);
		static void Shutdown();

		static void beginFrame();
		static void update();
		static void endFrame();

		static void trySetViewport(glm::uvec4 viewport);

		static void setClearColor(const glm::vec4& color);
		static void clear();
	private:
		// x, y = position of viewport
		// z, w = dimensions of viewport
		static glm::uvec4 m_LastViewport;

		friend class NimbleEngine;
		friend class Application;
	};
}
