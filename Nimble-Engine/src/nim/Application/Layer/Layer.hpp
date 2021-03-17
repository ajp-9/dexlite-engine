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

		virtual void onAttach() = 0;
		virtual void onDetach() = 0;

		virtual void onUpdate() = 0;
		virtual void onRender() = 0;
		virtual void onEvent(std::unique_ptr<event::Event>& e) = 0;
	public:
		uint m_Index = 0;
	};
}
