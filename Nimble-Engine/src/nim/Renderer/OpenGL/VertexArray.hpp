#pragma once

#include <vector>
#include "Buffers/VertexBuffer.hpp"
#include "Buffers/IndexBuffer.hpp"

namespace nim
{
	namespace gl
	{
		class VertexArray
		{
		public:
			VertexArray();
			~VertexArray();

			void render();
			void renderLines();

			void bind();
			void unbind();

			//void addVertexBuffer(const VertexBuffer& buffer);
			void setIndexBuffer(const IndexBuffer& buffer);
		private:
			uint32_t m_ID;
			//std::vector<VertexBuffer> m_VertexBuffers;
			IndexBuffer m_IndexBuffer;
		};
	}
}
