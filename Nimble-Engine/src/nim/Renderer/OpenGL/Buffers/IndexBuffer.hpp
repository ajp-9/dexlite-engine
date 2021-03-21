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
		private:
			uint32_t m_ID;
			uint32_t m_Count;
		};
	}
}
