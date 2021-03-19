#pragma once

#include <memory>

#include "../../Util/TypeDefs.hpp"
#include "Event/Event.hpp"

namespace nim
{
	class EngineHandle;

	class Layer
	{
	public:
		virtual void attach() = 0;
		virtual void detach() = 0;

		virtual void update() = 0;
		virtual void render() = 0;
		virtual void event(std::unique_ptr<event::Event>& e) = 0;
	public:
		uint m_Index = 0;
		// In order to get access to the class you need to include it.
		// Just a definition will not suffice.
		std::shared_ptr<EngineHandle> m_EngineHandle;
	};
}
