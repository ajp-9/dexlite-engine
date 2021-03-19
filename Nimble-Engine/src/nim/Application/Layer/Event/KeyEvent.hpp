#pragma once

#include "Event.hpp"

namespace nim
{
	namespace event
	{
		struct KeyEvent : Event
		{
			KeyEvent(uint16_t m_type, uint16_t keyCode) : Event(m_type), m_KeyCode(keyCode) {}
			uint16_t m_KeyCode;
		};
	}
}
