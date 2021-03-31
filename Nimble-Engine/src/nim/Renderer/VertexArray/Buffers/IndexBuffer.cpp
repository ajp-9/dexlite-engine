#include "IndexBuffer.hpp"

#include <glad/glad.h>
#include <iostream>

namespace nim
{
	namespace GL
	{
		IndexBuffer::IndexBuffer()
		{
			glGenBuffers(1, &m_ID);
			bind();
		}

		void IndexBuffer::uploadData(std::vector<unsigned int>& indices)
		{
			bind();
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
			m_Count = indices.size();
		}

		void IndexBuffer::bind()
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
		}
		void IndexBuffer::unbind()
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	}
}
