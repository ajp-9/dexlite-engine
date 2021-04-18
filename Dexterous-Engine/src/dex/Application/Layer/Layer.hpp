#pragma once

#include <memory>

#include "../../Util/TypeDefs.hpp"
#include "Event/Event.hpp"

namespace dex
{
	class Layer
	{
	public:
		virtual void Attach() = 0;
		virtual void Detach() = 0;

		virtual void update() = 0;
		virtual void render() = 0;
		virtual void event(std::unique_ptr<Event::Event>& e) = 0;
	public:
		uint m_Index = 0;
	};
}
