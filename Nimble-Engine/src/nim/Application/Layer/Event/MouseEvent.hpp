#pragma once

#include <glm/vec2.hpp>

#include "Event.hpp"

namespace nim
{
	namespace event
	{
		struct MouseEvent : Event
		{
			MouseEvent(uint8_t m_type, uint8_t mouseCode, glm::ivec2 mousePosition)
				: Event(m_type), m_MouseCode(mouseCode), m_MousePosition(mousePosition)
			{}

			uint8_t m_MouseCode;
			glm::ivec2 m_MousePosition;
		};

		namespace mouse
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
