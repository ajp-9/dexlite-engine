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


		}
	}
}
