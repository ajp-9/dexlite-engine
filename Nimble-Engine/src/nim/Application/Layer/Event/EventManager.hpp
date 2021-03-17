#pragma once

namespace nim
{
	namespace event
	{
		namespace type
		{
			enum
			{
				NONE,
				KEYBOARD,
				MOUSE,
				WINDOW
			};
		}

		class EventManager
		{
		public:
			EventManager();
		};
	}
}