#pragma once

#include <glm/vec2.hpp>

#include "Event.hpp"

namespace dex
{
	namespace Event
	{
		struct MouseEvent : Event
		{
			MouseEvent(uint8_t type, SDL_Event rawEvent, uint8_t mouseCode, glm::ivec2 mousePosition)
				: Event(type, rawEvent), m_MouseCode(mouseCode), m_MousePosition(mousePosition)
			{}

			uint8_t m_MouseCode;
			glm::ivec2 m_MousePosition;
		};

		struct ScrollEvent : Event
		{
			ScrollEvent(uint8_t type, SDL_Event rawEvent, int8_t scrollAmount)
				: Event(type, rawEvent), m_ScrollAmount(scrollAmount)
			{}

			int8_t m_ScrollAmount;
		};

		namespace Mouse
		{
			enum
			{
				MOVE,
				LEFT,
				MIDDLE,
				RIGHT,
				SCROLL_DOWN,
				SCROLL_UP
			};
		}
	}
}
