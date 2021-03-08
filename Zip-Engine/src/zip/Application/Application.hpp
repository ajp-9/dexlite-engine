#pragma once

#include "Window/Window.hpp"
#include <glm/vec2.hpp>

namespace zip
{
	class Application
	{
	public:
		Application();
		~Application();

		void update();
	private:
		Window m_Window;
	};
}
