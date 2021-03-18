#pragma once

#include <glm/vec2.hpp>

#include "Window/Window.hpp"
#include "Layer/LayerManager.hpp"

namespace nim
{
	class Application
	{
	public:
		Application();
		~Application();

		void update();
	private:
		Window m_Window;
		LayerManager m_LayerManager;
	};
}
