#pragma once

#include <stdint.h>
#include <SDL2/SDL_events.h>

namespace dex
{
	namespace Event
	{
		struct Event
		{
			Event(uint16_t type, SDL_Event rawEvent)
				: m_Type(type), m_RawEvent(rawEvent)
			{}

			// Put in the template the type of event.
			template <class T>
			inline T& getSelf()
			{
				return *static_cast<T*>(this);
			}
			
			uint16_t m_Type = 0;
			SDL_Event m_RawEvent;
			bool m_Handled = false;
		};

		namespace Type
		{
			enum
			{
				NONE,
				KEYBOARD,
				KEY_DOWN,
				KEY_UP,
				TEXT_INPUT,
				MOUSE_MOVE,
				MOUSE_DOWN,
				MOUSE_UP,
				MOUSE_SCROLL,
				WINDOW
			};
		}
	}
}
