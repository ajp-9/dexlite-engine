#include "VertexArray.hpp"

#include <glad/glad.h>

namespace nim
{
	namespace gl
	{
		VertexArray::VertexArray()
		{
			glGenVertexArrays(1, &m_ID);
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

		void VertexArray::renderLines()
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

		void VertexArray::addVertexBuffer(const VertexBuffer& buffer)
		{
			bind();
			m_VertexBuffers.emplace_back(buffer);
		}

		void VertexArray::setIndexBuffer(const IndexBuffer& buffer)
		{
			bind();
			m_IndexBuffer = buffer;
		}
	}
}
