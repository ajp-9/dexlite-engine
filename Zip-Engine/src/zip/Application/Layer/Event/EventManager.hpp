#pragma once

namespace zip
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