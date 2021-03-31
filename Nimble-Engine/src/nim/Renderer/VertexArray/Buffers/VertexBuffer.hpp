#pragma once

#include <vector>
#include <iostream>
#include <glad/glad.h>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

namespace nim
{
	// BEFORE you do ANYTHING, bind the VAO!
	// Template for type of vertex.
	template <typename V>
	class VertexBuffer
	{
	public:
		VertexBuffer();

		void uploadData(const std::vector<V>& vertices);

		void bind();
		void unbind();

		// Specify the layout of each vertex with templates.
		template <typename ...Ts> 
		void setVertexLayout();
	private:
		template <typename T>
		inline void addLocation();
	private:
		uint32_t m_ID = 0;
		uint8_t m_LayoutSize = 0;
		uint8_t m_CurrentOffset = 0;
	};

	namespace bufferType
	{
		enum
		{
			ARRAY = GL_ARRAY_BUFFER,
			ELEMENT = GL_ELEMENT_ARRAY_BUFFER
		};
	}

	namespace bufferDrawHint
	{
		enum
		{
			STATIC = GL_STATIC_DRAW
		};
	}

	// Implementation

	template <typename V>
	VertexBuffer<V>::VertexBuffer()
	{
		glGenBuffers(1, &m_ID);
	}

	template <typename V>
	void VertexBuffer<V>::uploadData(const std::vector<V>& vertices)
	{
		bind();
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(V), &vertices[0], GL_STATIC_DRAW);
	}

	template <typename V>
	void VertexBuffer<V>::bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
	}
	template <typename V>
	void VertexBuffer<V>::unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	template <typename V>
	template <typename ...Ts>
	void VertexBuffer<V>::setVertexLayout()
	{
		bind();
		int types[] = { 0, (addLocation<Ts>(), 0)... };
		// Suppresses compile warnings
		(void)types;
	}

	template <typename V>
	template <typename T>
	void VertexBuffer<V>::addLocation()
	{
		bind();
		uint32_t varAmount = 0;

		uint32_t varType = 0;

		// In order of most likely, but defaults to 1
		if (std::is_same<T, glm::vec3>::value ||
			std::is_same<T, glm::uvec3>::value ||
			std::is_same<T, glm::ivec3>::value ||
			std::is_same<T, glm::dvec3>::value)
			varAmount = 3;
		else if (std::is_same<T, glm::vec2>::value ||
			std::is_same<T, glm::uvec2>::value ||
			std::is_same<T, glm::ivec2>::value ||
			std::is_same<T, glm::dvec2>::value)
			varAmount = 2;
		else if (std::is_same<T, glm::vec4>::value ||
			std::is_same<T, glm::uvec4>::value ||
			std::is_same<T, glm::ivec4>::value ||
			std::is_same<T, glm::dvec4>::value)
			varAmount = 4;
		else
			varAmount = 1;

		// Defaults to GL_FLOAT
		if (std::is_same<T, glm::vec2>::value ||
			std::is_same<T, glm::vec3>::value ||
			std::is_same<T, glm::vec4>::value ||
			std::is_same<T, float>::value)
			varType = GL_FLOAT;
		else if (std::is_same<T, glm::uvec2>::value ||
			std::is_same<T, glm::uvec3>::value ||
			std::is_same<T, glm::uvec4>::value ||
			std::is_same<T, unsigned int>::value)
			varType = GL_UNSIGNED_INT;
		else if (std::is_same<T, glm::ivec2>::value ||
			std::is_same<T, glm::ivec3>::value ||
			std::is_same<T, glm::ivec4>::value ||
			std::is_same<T, int>::value)
			varType = GL_INT;
		else if (std::is_same<T, unsigned char>::value)
			varType = GL_UNSIGNED_BYTE;
		else
			varType = GL_FLOAT;

		glEnableVertexAttribArray(m_LayoutSize);

		if(varType != GL_UNSIGNED_INT && varType != GL_INT && varType != GL_UNSIGNED_BYTE)
			glVertexAttribPointer(m_LayoutSize, varAmount, varType, GL_FALSE, sizeof(V), (const void*)m_CurrentOffset);
		else
			glVertexAttribIPointer(m_LayoutSize, varAmount, varType, sizeof(V), (const void*)m_CurrentOffset);

		//std::cout << (unsigned)m_LayoutSize << ", " << varAmount << ", " << varType << ", " << GL_FALSE << ", " << sizeof(V) << ", " << (unsigned)m_CurrentByteStep << "\n";

		m_CurrentOffset += sizeof(T);
		m_LayoutSize++;
	}
}
