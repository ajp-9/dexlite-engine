#pragma once

#include "../../Util/TypeDefs.hpp"

namespace nim
{
	class Layer
	{
	public:
		Layer(uint index) 
			: m_Index(index)
		{}

		virtual void onAttach() = 0;
		virtual void onDetach() = 0;

		virtual void onUpdate() = 0;
		virtual void onEvent() = 0;
	private:
		uint m_Index = 0;
	};
}
