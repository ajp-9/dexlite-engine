#include "EventManager.hpp"

#include <SDL2/SDL.h>

#include "../../../Core/NimbleEngine.hpp"
#include "KeyEvent.hpp"
#include "MouseEvent.hpp"

namespace nim
{
	std::vector<std::unique_ptr<event::Event>> nim::EventManager::getEventQueue()
	{
		std::vector<std::unique_ptr<event::Event>> events;

		SDL_Event evt;
		while (SDL_PollEvent(&evt))
		{
			switch (evt.type)
			{
			case SDL_MOUSEMOTION:
				glm::ivec2 mousePos;
				SDL_GetMouseState(&mousePos.x, &mousePos.y);
				events.emplace_back(std::make_unique<event::MouseEvent>(event::type::MOUSE_MOVE, evt, event::mouse::MOVE, mousePos));
				break;
			case SDL_KEYDOWN:
				events.emplace_back(std::make_unique<event::KeyEvent>(event::type::KEY_DOWN, evt, evt.key.keysym.scancode));
				break;
			case SDL_KEYUP:
				events.emplace_back(std::make_unique<event::KeyEvent>(event::type::KEY_UP, evt, evt.key.keysym.scancode));
				break;
			case SDL_MOUSEBUTTONDOWN:
				events.emplace_back(std::make_unique<event::MouseEvent>(event::type::MOUSE_DOWN, evt, evt.button.button, glm::vec2(evt.button.x, evt.button.y)));
				break;
			case SDL_MOUSEBUTTONUP:
				events.emplace_back(std::make_unique<event::MouseEvent>(event::type::MOUSE_UP, evt, evt.button.button, glm::vec2(evt.button.x, evt.button.y)));
				break;
			case SDL_MOUSEWHEEL:
				events.emplace_back(std::make_unique<event::ScrollEvent>(event::type::MOUSE_SCROLL, evt, evt.wheel.y));
				break;
			case SDL_QUIT:
				NimbleEngine::m_Running = false;
				break;
			default:
				break;
			}
		}

		const Uint8* k = SDL_GetKeyboardState(NULL);

		for (uint16_t i = 0; i < event::key::MAX_KEY; i++)
			if (k[i])
				events.emplace_back(std::make_unique<event::KeyEvent>(event::type::KEYBOARD, evt, i));

		return events;
	}
}
