#pragma once

#include <glm/vec2.hpp>
#include <vector>
#include <memory>

#include "EventBase.hpp"

namespace dex
{
	namespace Event
	{
		class Manager
		{
		public:
			static std::vector<std::unique_ptr<Event::Base>> getEventQueue();
		};
	}
}
