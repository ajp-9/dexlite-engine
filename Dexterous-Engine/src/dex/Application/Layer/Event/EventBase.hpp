#pragma once

#include <stdint.h>

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
			Base(Type type)
				: m_Type(type)
			{}

			// Put in the template the type of event.
			template <class T>
			inline T& getDerivedSelf()
			{
				if (typeid(T) != typeid(*this))
					std::cout << "Error: The template input: (" << typeid(T).name() << ") can't be derived from the current object (" << typeid(*this).name() << ").\n";

				return *static_cast<T*>(this);
			}
			
			Type m_Type = Type::NONE;
			bool m_Handled = false;
		};
	}
}
