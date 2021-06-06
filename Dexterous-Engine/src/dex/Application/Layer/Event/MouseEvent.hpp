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
			MouseEvent(Type type, MouseType mouseCode, glm::ivec2 mousePosition)
				: Base(type), m_MouseCode(mouseCode), m_MousePosition(mousePosition)
			{}

			MouseType m_MouseCode;
			glm::ivec2 m_MousePosition;
		};

		struct ScrollEvent : Base
		{
			ScrollEvent(Type type, int8_t scrollAmount)
				: Base(type), m_ScrollAmount(scrollAmount)
			{}

			int8_t m_ScrollAmount;
		};
	}
}
