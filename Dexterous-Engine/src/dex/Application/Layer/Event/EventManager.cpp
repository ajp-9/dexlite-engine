#include "EventManager.hpp"

#include <SDL2/SDL.h>
#include <imgui/imgui_impl_sdl.h>

#include "../../../Core/Engine.hpp"
#include "KeyEvent.hpp"
#include "MouseEvent.hpp"

namespace dex
{
	std::vector<std::unique_ptr<Event::Event>> EventManager::getEventQueue()
	{
		std::vector<std::unique_ptr<Event::Event>> events;

		SDL_Event evt;
		while (SDL_PollEvent(&evt))
		{
			switch (evt.type)
			{
			case SDL_MOUSEMOTION:
				glm::ivec2 mousePos;
				SDL_GetMouseState(&mousePos.x, &mousePos.y);
				events.emplace_back(std::make_unique<Event::MouseEvent>(Event::Type::MOUSE_MOVE, evt, Event::Mouse::MOVE, mousePos));
				break;
			case SDL_KEYDOWN:
				events.emplace_back(std::make_unique<Event::KeyEvent>(Event::Type::KEY_DOWN, evt, evt.key.keysym.scancode));
				break;
			case SDL_KEYUP:
				events.emplace_back(std::make_unique<Event::KeyEvent>(Event::Type::KEY_UP, evt, evt.key.keysym.scancode));
				break;
			case SDL_TEXTINPUT:
				ImGui_ImplSDL2_ProcessEvent(&evt);
				break;
			case SDL_MOUSEBUTTONDOWN:
				events.emplace_back(std::make_unique<Event::MouseEvent>(Event::Type::MOUSE_DOWN, evt, evt.button.button, glm::vec2(evt.button.x, evt.button.y)));
				break;
			case SDL_MOUSEBUTTONUP:
				events.emplace_back(std::make_unique<Event::MouseEvent>(Event::Type::MOUSE_UP, evt, evt.button.button, glm::vec2(evt.button.x, evt.button.y)));
				break;
			case SDL_MOUSEWHEEL:
				events.emplace_back(std::make_unique<Event::ScrollEvent>(Event::Type::MOUSE_SCROLL, evt, evt.wheel.y));
				break;
			case SDL_QUIT:
				Engine::m_Running = false;
				break;
			default:
				break;
			}
		}

		const Uint8* k = SDL_GetKeyboardState(NULL);

		for (uint16_t i = 0; i < Event::Key::MAX_KEY; i++)
			if (k[i])
				events.emplace_back(std::make_unique<Event::KeyEvent>(Event::Type::KEYBOARD, evt, i));

		return events;
	}
}
