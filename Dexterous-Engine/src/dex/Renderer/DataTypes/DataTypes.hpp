#pragma once

#include <iostream>

namespace dex
{
	namespace Data
	{
		enum class Type : uint16_t
		{
			BOOL,

			CHAR,

			INT,
			IVEC2,
			IVEC3,
			IVEC4,

			UINT,
			UVEC2,
			UVEC3,
			UVEC4,

			FLOAT,
			VEC2,
			VEC3,
			VEC4,

			DOUBLE,
			DVEC2,
			DVEC3,
			DVEC4,

			MAT2,
			MAT3,
			MAT4
		};

		uint32_t getGLType(Type type);

		uint32_t getTypeSize(Type type);

		uint32_t getTypeAmount(Type type);

		uint32_t get_std140_BaseAlignment(Type type);
	}
}
