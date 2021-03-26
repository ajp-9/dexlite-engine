#include "VertexBuffer.hpp"

namespace nim
{
	namespace gl
	{
		template <typename V>
		void VertexBuffer<V>::bind()
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		}

		template <typename V>
		void VertexBuffer<V>::unbind()
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	}
}
