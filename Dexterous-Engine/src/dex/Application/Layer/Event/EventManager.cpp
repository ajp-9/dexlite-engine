#include "EventManager.hpp"

#include <SDL2/SDL.h>
#include <imgui/imgui_impl_sdl.h>

#include "../../../Core/Engine.hpp"
#include "KeyEvent.hpp"
#include "MouseEvent.hpp"

namespace dex
{
	namespace Event
	{
		std::vector<std::unique_ptr<Event::Base>> Manager::getEventQueue()
		{
			std::vector<std::unique_ptr<Event::Base>> events;

			SDL_Event evt;
			while (SDL_PollEvent(&evt))
			{
				switch (evt.type)
				{
				case SDL_MOUSEMOTION:
					glm::ivec2 mousePos;
					SDL_GetMouseState(&mousePos.x, &mousePos.y);
					events.emplace_back(std::make_unique<Event::MouseEvent>(Event::Type::MOUSE_MOVE, evt, Event::MouseType::MOVE, mousePos));
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
					events.emplace_back(std::make_unique<Event::MouseEvent>(Event::Type::MOUSE_DOWN, evt, Event::MouseType(evt.button.button), glm::vec2(evt.button.x, evt.button.y)));
					break;
				case SDL_MOUSEBUTTONUP:
					events.emplace_back(std::make_unique<Event::MouseEvent>(Event::Type::MOUSE_UP, evt, Event::MouseType(evt.button.button), glm::vec2(evt.button.x, evt.button.y)));
					break;
				case SDL_MOUSEWHEEL:
					events.emplace_back(std::make_unique<Event::ScrollEvent>(Event::Type::MOUSE_SCROLL, evt, evt.wheel.y));
					break;
				case SDL_QUIT:
					Engine::Stop();
					break;
				default:
					break;
				}
			}

			const Uint8* k = SDL_GetKeyboardState(NULL);

			for (uint32_t i = 0; i < uint32_t(Event::Key::MAX_KEY); i++)
				if (k[i])
					events.emplace_back(std::make_unique<Event::KeyEvent>(Event::Type::KEYBOARD, evt, i));

			return events;
		}
	}
}
