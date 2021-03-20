#pragma once

#include <glm/vec2.hpp>

#include "Window/Window.hpp"
#include "Layer/LayerManager.hpp"

namespace nim
{
	class Application
	{
	public:
		Application(std::shared_ptr<EngineHandle>& engineHandle);
		~Application() {}

		void update();
	public:
		Window m_Window;
		LayerManager m_LayerManager;
	};
}
