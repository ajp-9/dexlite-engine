#include "VertexArray.hpp"

namespace dex
{
	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_ID);
		bind();
	}

	VertexArray::~VertexArray()
	{
		//glDeleteVertexArrays(1, &m_ID);
	}

	void VertexArray::render()
	{
		bind();
		glDrawElements(GL_TRIANGLES, m_IndexBuffer.getCount(), GL_UNSIGNED_INT, 0);
	}

	void VertexArray::renderAsLines()
	{
		bind();
		glDrawElements(GL_LINES, m_IndexBuffer.getCount(), GL_UNSIGNED_INT, 0);
	}

	void VertexArray::bind()
	{
		glBindVertexArray(m_ID);
	}

	void VertexArray::unbind()
	{
		glBindVertexArray(0);
	}
}
