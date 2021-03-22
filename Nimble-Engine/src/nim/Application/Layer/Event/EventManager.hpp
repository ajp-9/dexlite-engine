#pragma once

#include <glm/vec2.hpp>
#include <vector>
#include <memory>

#include "Event.hpp"

namespace nim
{
	class EventManager
	{
	public:
		static std::vector<std::unique_ptr<event::Event>> getEventQueue();
	};
}
