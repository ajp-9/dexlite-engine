#pragma once

#include "Event.hpp"

namespace nim
{
	namespace event
	{
		struct KeyEvent : Event
		{
			KeyEvent(uint16_t m_type, uint16_t keyCode) 
                : Event(m_type), m_KeyCode(keyCode) 
            {}

			uint16_t m_KeyCode;
		};

        // These values are from usage page 0x07 (USB keyboard page).
        namespace key
        {
            enum
            {
                UNKNOWN = 0,

                A = 4,
                B = 5,
                C = 6,
                D = 7,
                E = 8,
                F = 9,
                G = 10,
                H = 11,
                I = 12,
                J = 13,
                K = 14,
                L = 15,
                M = 16,
                N = 17,
                O = 18,
                P = 19,
                Q = 20,
                R = 21,
                S = 22,
                T = 23,
                U = 24,
                V = 25,
                W = 26,
                X = 27,
                Y = 28,
                Z = 29,

                n1 = 30,
                n2 = 31,
                n3 = 32,
                n4 = 33,
                n5 = 34,
                n6 = 35,
                n7 = 36,
                n8 = 37,
                n9 = 38,
                n0 = 39,

                RETURN = 40,
                ESCAPE = 41,
                BACKSPACE = 42,
                TAB = 43,
                SPACE = 44,

                MINUS = 45,
                EQUALS = 46,
                LEFTBRACKET = 47,
                RIGHTBRACKET = 48,

                SEMICOLON = 51,
                APOSTROPHE = 52,
                GRAVE = 53,
                COMMA = 54,
                PERIOD = 55,
                SLASH = 56,

                CAPSLOCK = 57,

                F1 = 58,
                F2 = 59,
                F3 = 60,
                F4 = 61,
                F5 = 62,
                F6 = 63,
                F7 = 64,
                F8 = 65,
                F9 = 66,
                F10 = 67,
                F11 = 68,
                F12 = 69,

                PRINTSCREEN = 70,
                SCROLLLOCK = 71,
                PAUSE = 72,
                INSERT = 73,
                HOME = 74,
                PAGEUP = 75,
                DELETE = 76,
                END = 77,
                PAGEDOWN = 78,
                RIGHT = 79,
                LEFT = 80,
                DOWN = 81,
                UP = 82,

                // Keypad
                KP_DIVIDE = 84,
                KP_MULTIPLY = 85,
                KP_MINUS = 86,
                KP_PLUS = 87,
                KP_ENTER = 88,
                KP_1 = 89,
                KP_2 = 90,
                KP_3 = 91,
                KP_4 = 92,
                KP_5 = 93,
                KP_6 = 94,
                KP_7 = 95,
                KP_8 = 96,
                KP_9 = 97,
                KP_0 = 98,
                KP_PERIOD = 99,
                MAX_KEY = 100
            };
        }
	}
}
