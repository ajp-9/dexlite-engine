#include "VertexBuffer.hpp"

namespace nim
{
	VertexBuffer::VertexBuffer()
	{
		glGenBuffers(1, &m_ID);
	}

	void VertexBuffer::bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
	}

	void VertexBuffer::unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}
