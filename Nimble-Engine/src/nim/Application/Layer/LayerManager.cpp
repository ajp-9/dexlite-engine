#include "LayerManager.hpp"

#include <SDL2/SDL.h>

#include "Event/KeyEvent.hpp"
#include "Event/MouseEvent.hpp"

namespace nim
{
	LayerManager::LayerManager()
	{
	}

	void LayerManager::pushLayer(std::shared_ptr<Layer> layer)
	{
		layer->m_Index = m_Layers.size();
		m_Layers.push_back(layer);
		layer->Attach();
	}

	void LayerManager::popLayer()
	{
		m_Layers.at(m_Layers.size() - 1)->Detach();
		m_Layers.pop_back();
	}

	void LayerManager::updateLayers()
	{
		for (auto& l : m_Layers)
			l->update();
	}

	void LayerManager::renderLayers()
	{
		for (auto& l : m_Layers)
			l->render();
	}

	void LayerManager::sendEvents()
	{
		auto events = getEventQueue();

		for (auto& e : events)
		{
			for (auto& l : m_Layers)
			{
				l->event(e);

				if (e->m_Handled)
					return;
			}
		}
	}

	std::vector<std::unique_ptr<event::Event>> LayerManager::getEventQueue()
	{
		std::vector<std::unique_ptr<event::Event>> events;

		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_MOUSEMOTION:
				glm::ivec2 mousePos;
				SDL_GetMouseState(&mousePos.x, &mousePos.y);
				events.emplace_back(std::make_unique<event::MouseEvent>(event::type::MOUSE_MOVE, event::mouse::MOVE, mousePos));
				break;
			case SDL_KEYDOWN:
				events.emplace_back(std::make_unique<event::KeyEvent>(event::type::KEY_DOWN, e.key.keysym.scancode));
				break;
			case SDL_KEYUP:
				events.emplace_back(std::make_unique<event::KeyEvent>(event::type::KEY_UP, e.key.keysym.scancode));
				break;
			case SDL_MOUSEBUTTONDOWN:
				events.emplace_back(std::make_unique<event::MouseEvent>(event::type::MOUSE_DOWN, e.button.button, glm::vec2(e.button.x, e.button.y)));
				break;
			case SDL_MOUSEBUTTONUP:
				events.emplace_back(std::make_unique<event::MouseEvent>(event::type::MOUSE_UP, e.button.button, glm::vec2(e.button.x, e.button.y)));
				break;
			case SDL_QUIT:
				//NimbleEngine::shutdown();
				break;
			default:
				break;
			}
		}

		const Uint8* k = SDL_GetKeyboardState(NULL);

		for (uint16_t i = 0; i < event::key::MAX_KEY; i++)
			if (k[i])
				events.emplace_back(std::make_unique<event::KeyEvent>(event::type::KEYBOARD, i));

		return events;
	}
}
