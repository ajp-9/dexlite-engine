#pragma once

#include <glm/vec2.hpp>

#include "Window/Window.hpp"
#include "Layer/LayerManager.hpp"

namespace nim
{
	class Application
	{
		Application(glm::ivec2 dimensions);
		~Application() {}
	public:
		void update();
	public:
		Window m_Window;
		LayerManager m_LayerManager;

		friend class NimbleEngine;
	};
}
