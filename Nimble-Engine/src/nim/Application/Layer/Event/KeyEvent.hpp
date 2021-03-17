#pragma once

#include "Event.hpp"

namespace nim
{
	namespace event
	{
		struct KeyEvent : Event
		{
			uint16_t m_KeyCode;
		};
	}
}
