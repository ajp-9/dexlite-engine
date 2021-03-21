#pragma once

#include <cstdint>

namespace nim
{
	namespace gl
	{
		class IndexBuffer
		{
		public:
			IndexBuffer();

			uint32_t getCount() const { return m_Count; }
		private:
			uint32_t m_ID;
			uint32_t m_Count;
		};
	}
}
