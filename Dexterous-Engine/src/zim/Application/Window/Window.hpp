#pragma once

#include <glm/vec2.hpp>
#include <SDL2/SDL.h>
#include <vector>
#include <memory>

#include "../Layer/Event/Event.hpp"

namespace zim
{
	class Window
	{
		Window(glm::uvec2 windowDimensions);
		~Window();

		void update();
	public:
		glm::ivec2 getDimensions();
	private:
		SDL_Window* m_Window;
		SDL_GLContext m_GLContext;

		friend class ZimbleEngine;
		friend class ImGuiAPI;
	};
}