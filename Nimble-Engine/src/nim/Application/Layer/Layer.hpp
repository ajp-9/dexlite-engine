#pragma once

#include <memory>

#include "../../Util/TypeDefs.hpp"
#include "Event/Event.hpp"

namespace nim
{
	class Layer
	{
	public:
		Layer() {}

		virtual void attach() = 0;
		virtual void detach() = 0;

		virtual void update() = 0;
		virtual void render() = 0;
		virtual void event(std::unique_ptr<event::Event>& e) = 0;
	public:
		uint m_Index = 0;
	};
}
