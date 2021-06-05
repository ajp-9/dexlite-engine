#pragma once

#include <glad/glad.h>
#include <vector>

#include "../../../DataTypes/DataTypes.hpp"

namespace dex
{
	enum class BufferDrawHint : uint32_t
	{
		STATIC = GL_STATIC_DRAW,
		DYNAMIC = GL_DYNAMIC_DRAW
	};

	// BEFORE you do ANYTHING to the children, bind the Array (Parent)!
	class VertexBuffer
	{
	public:
		VertexBuffer();

		template <typename V>
		void uploadData(const std::vector<V>& vertices, BufferDrawHint drawHint = BufferDrawHint::STATIC);
		
		void bind();
		void unbind();

		template <typename V>
		void setVertexLayout(const std::vector<Data::Type>& types);
	private:
		uint32_t m_ID = 0;
	};

	/*
	** Implementation:
	*/

	template<typename V>
	inline void VertexBuffer::uploadData(const std::vector<V>& vertices, BufferDrawHint drawHint)
	{
		bind();
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(V), &vertices[0], uint32_t(drawHint));
	}

	template<typename V>
	inline void dex::VertexBuffer::setVertexLayout(const std::vector<Data::Type>& types)
	{
		bind();

		uint8_t currentOffset = 0;

		for (uint32_t i = 0; i < types.size(); i++)
		{
			Data::Type d_type = types.at(i);

			uint32_t d_gl_type = Data::getGLType(d_type);
			uint32_t d_size = Data::getTypeSize(d_type);
			uint32_t d_amount = Data::getTypeAmount(d_type);

			glEnableVertexAttribArray(i);

			if (d_type == Data::Type::BOOL ||
				d_type == Data::Type::CHAR ||
				d_type == Data::Type::DOUBLE ||
				d_type == Data::Type::DVEC2 ||
				d_type == Data::Type::DVEC3 ||
				d_type == Data::Type::DVEC4 ||
				d_type == Data::Type::INT ||
				d_type == Data::Type::IVEC2 ||
				d_type == Data::Type::IVEC3 ||
				d_type == Data::Type::IVEC4 ||
				d_type == Data::Type::UINT ||
				d_type == Data::Type::UVEC2 ||
				d_type == Data::Type::UVEC3 ||
				d_type == Data::Type::UVEC4)
			{
				glVertexAttribIPointer(i, d_amount, d_gl_type, sizeof(V), (const void*)currentOffset);
			}
			else
			{
				glVertexAttribPointer(i, d_amount, d_gl_type, GL_FALSE, sizeof(V), (const void*)currentOffset);
			}

			currentOffset += d_size;
		}
	}
}
