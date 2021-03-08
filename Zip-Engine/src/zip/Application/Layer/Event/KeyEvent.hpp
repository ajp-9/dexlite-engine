#pragma once

#include "Event.hpp"

namespace zip
{
	namespace event
	{
		struct KeyEvent : Event
		{
			uint16_t m_KeyCode;
		};
	}
}
