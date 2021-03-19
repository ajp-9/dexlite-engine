#pragma once

#include <stdint.h>

namespace nim
{
	namespace event
	{
		struct Event
		{
			Event(uint16_t type)
				: m_Type(type)
			{}

			// Put in template the type of event
			template <class T>
			inline T& getSelfSubstruct()
			{
				return *static_cast<T*>(this);
			}
			
			uint16_t m_Type = 0;
			bool m_Handled = false;
		};

		namespace type
		{
			enum
			{
				NONE,
				KEYBOARD,
				KEY_DOWN,
				KEY_UP,
				MOUSE,
				WINDOW
			};
		}
	}
}
