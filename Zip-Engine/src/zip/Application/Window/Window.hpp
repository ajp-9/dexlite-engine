#pragma once

#include <glm/vec2.hpp>
#include <SDL2/SDL.h>
#include <vector>
#include <memory>

#include "../Layer/Event/Event.hpp"

namespace zip
{
	class Window
	{
	public:
		Window(glm::ivec2 windowDimensions);
		~Window();

		void update();

		glm::ivec2 getDimensions();

		std::vector<std::unique_ptr<event::Event>> getEventQueue();
	private:
		inline void setupOpenGL();
	private:
		SDL_Window* m_Window;
		SDL_GLContext m_GLContext;
	};
}
