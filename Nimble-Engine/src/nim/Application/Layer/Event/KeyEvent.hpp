#pragma once

#include "Event.hpp"

namespace nim
{
	namespace event
	{
		struct KeyEvent : Event
		{
			KeyEvent(uint16_t keyCode) : m_KeyCode(keyCode) {}
			uint16_t m_KeyCode;
		};
	}
}
