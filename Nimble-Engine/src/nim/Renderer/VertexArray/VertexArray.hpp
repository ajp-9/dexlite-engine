#pragma once

#include <vector>
#include "Buffers/VertexBuffer.hpp"
#include "Buffers/IndexBuffer.hpp"

namespace nim
{
	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		void render();
		void renderAsLines();

		void bind();
		void unbind();
	public:
		VertexBuffer m_VertexBuffers;
		IndexBuffer m_IndexBuffer;
	private:
		uint32_t m_ID;
	};
}
