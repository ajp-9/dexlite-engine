#pragma once

#include <glm/vec2.hpp>

#include "EventBase.hpp"

namespace dex
{
	namespace Event
	{
		enum class MouseType : uint32_t
		{
			MOVE,
			LEFT,
			MIDDLE,
			RIGHT,
			SCROLL_DOWN,
			SCROLL_UP
		};

		struct MouseEvent : Base
		{
			MouseEvent(Type type, SDL_Event rawEvent, MouseType mouseCode, glm::ivec2 mousePosition)
				: Base(type, rawEvent), m_MouseCode(mouseCode), m_MousePosition(mousePosition)
			{}

			MouseType m_MouseCode;
			glm::ivec2 m_MousePosition;
		};

		struct ScrollEvent : Base
		{
			ScrollEvent(Type type, SDL_Event rawEvent, int8_t scrollAmount)
				: Base(type, rawEvent), m_ScrollAmount(scrollAmount)
			{}

			int8_t m_ScrollAmount;
		};
	}
}
