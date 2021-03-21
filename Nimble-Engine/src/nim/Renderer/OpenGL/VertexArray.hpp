#pragma once

#include <cstdint>
#include "VertexBuffer.hpp"

namespace nim
{
	namespace gl
	{
		class VertexArray
		{
		public:
			VertexArray();

			void bind();
			void unbind();

			void addVertexBuffer(const VertexBuffer& buffer);
		private:
			uint32_t m_ID;
		};
	}
}
