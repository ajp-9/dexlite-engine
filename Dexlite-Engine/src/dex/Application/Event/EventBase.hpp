#pragma once

#include "../../Util/Typedefs.hpp"

namespace dex
{
    namespace Event
    {
        enum class Type : uint32
        {
            UNKNOWN,
            KEYBOARD,
            KEY_PRESS,
            KEY_RELEASE,
            TEXT_INPUT,
            MOUSE,
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
                //if (typeid(T) != typeid(*this))
                //    std::cout << "Error: The template input: (" << typeid(T).name() << ") can't be derived from the current object (" << typeid(*this).name() << ").\n";

                return *static_cast<T*>(this);
            }
            
            Type m_Type = Type::UNKNOWN;
            bool m_Handled = false;
        };
    }
}
