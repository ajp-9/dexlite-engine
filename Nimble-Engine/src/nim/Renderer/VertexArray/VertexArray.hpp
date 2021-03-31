#pragma once

#include <vector>
#include "Buffers/VertexBuffer.hpp"
#include "Buffers/IndexBuffer.hpp"

namespace nim
{
	template <typename V>
	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		void render();
		void renderAsLines();

		void bind();
		void unbind();

		//void addVertexBuffer(const VertexBuffer& buffer);
		void setIndexBuffer(const IndexBuffer& buffer);
	public:
		VertexBuffer<V> m_VertexBuffers;
		IndexBuffer m_IndexBuffer;
	private:
		uint32_t m_ID;
	};

	// Implementation

	template <typename V>
	VertexArray<V>::VertexArray()
	{
		glGenVertexArrays(1, &m_ID);
		bind();
	}

	template <typename V>
	VertexArray<V>::~VertexArray()
	{
		//glDeleteVertexArrays(1, &m_ID);
	}

	template <typename V>
	void VertexArray<V>::render()
	{
		bind();
		glDrawElements(GL_TRIANGLES, m_IndexBuffer.getCount(), GL_UNSIGNED_INT, 0);
	}

	template <typename V>
	void VertexArray<V>::renderAsLines()
	{
		bind();
		glDrawElements(GL_LINES, m_IndexBuffer.getCount(), GL_UNSIGNED_INT, 0);
	}

	template <typename V>
	void VertexArray<V>::bind()
	{
		glBindVertexArray(m_ID);
	}

	template <typename V>
	void VertexArray<V>::unbind()
	{
		glBindVertexArray(0);
	}

	template <typename V>
	void VertexArray<V>::setIndexBuffer(const IndexBuffer& buffer)
	{
		bind();
		m_IndexBuffer = buffer;
	}
	
}
