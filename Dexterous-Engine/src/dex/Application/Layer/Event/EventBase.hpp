#pragma once

#include <stdint.h>
#include <SDL2/SDL_events.h>

namespace dex
{
	namespace Event
	{
		enum class Type : uint32_t
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

		struct Base
		{
			Base(Type type, SDL_Event rawEvent)
				: m_Type(type), m_RawEvent(rawEvent)
			{}

			// Put in the template the type of event.
			template <class T>
			inline T& getSelf()
			{
				return *static_cast<T*>(this);
			}
			
			Type m_Type = Type::NONE;
			SDL_Event m_RawEvent;
			bool m_Handled = false;
		};
	}
}
