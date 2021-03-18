#pragma once

#include <stdint.h>

namespace nim
{
	namespace event
	{
		struct Event
		{
			uint16_t m_Type;
			bool m_Handled = false;
		};
	}
}