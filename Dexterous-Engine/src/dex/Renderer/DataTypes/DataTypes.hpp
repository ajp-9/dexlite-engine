#pragma once

#include <iostream>

#include "../../Util/Typedefs.hpp"

namespace dex
{
	namespace Data
	{
		enum class Type : uint16
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

		uint32 getGLType(Type type);

		uint32 getTypeSize(Type type);

		uint32 getTypeAmount(Type type);

		uint32 get_std140_BaseAlignment(Type type);
	}
}
