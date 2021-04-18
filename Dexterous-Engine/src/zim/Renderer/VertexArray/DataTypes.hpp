#pragma once

#include <iostream>

namespace zim
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

		unsigned int getGLType(Type type);

		unsigned getTypeSize(Type type);

		unsigned getTypeAmount(Type type);
	}
}
