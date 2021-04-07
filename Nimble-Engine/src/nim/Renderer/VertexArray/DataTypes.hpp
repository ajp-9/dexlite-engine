#pragma once

namespace nim
{
	enum class DataType
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

	static unsigned getDataTypeSize(DataType type)
	{
		switch (type)
		{
		case DataType::BOOL: return sizeof(bool);

		case DataType::CHAR: return sizeof(char);

		case DataType::INT : return sizeof(int) * 1;
		case DataType::IVEC2: return sizeof(int) * 2;
		case DataType::IVEC3: return sizeof(int) * 3;
		case DataType::IVEC4: return sizeof(int) * 4;

		case DataType::UINT : return sizeof(unsigned int) * 1;
		case DataType::UVEC2: return sizeof(unsigned int) * 2;
		case DataType::UVEC3: return sizeof(unsigned int) * 3;
		case DataType::UVEC4: return sizeof(unsigned int) * 4;

		case DataType::FLOAT  : return sizeof(float) * 1;
		case DataType::VEC2 : return sizeof(float) * 2;
		case DataType::VEC3 : return sizeof(float) * 3;
		case DataType::VEC4 : return sizeof(float) * 4;

		case DataType::DOUBLE: return sizeof(double) * 1;
		case DataType::DVEC2: return sizeof(double) * 2;
		case DataType::DVEC3: return sizeof(double) * 3;
		case DataType::DVEC4: return sizeof(double) * 4;

		case DataType::MAT2: return sizeof(float) * 4;
		case DataType::MAT3: return sizeof(float) * 9;
		case DataType::MAT4: return sizeof(float) * 16;
		}
	}

	static unsigned getDataTypeAmount(DataType type)
	{
		switch (type)
		{
		case DataType::BOOL: return 1;

		case DataType::CHAR: return 1;

		case DataType::INT: return 1;
		case DataType::IVEC2: return 2;
		case DataType::IVEC3: return 3;
		case DataType::IVEC4: return 4;

		case DataType::UINT: return 1;
		case DataType::UVEC2: return 2;
		case DataType::UVEC3: return 3;
		case DataType::UVEC4: return 4;

		case DataType::FLOAT: return 1;
		case DataType::VEC2: return 2;
		case DataType::VEC3: return 3;
		case DataType::VEC4: return 4;

		case DataType::DOUBLE: return 1;
		case DataType::DVEC2: return 2;
		case DataType::DVEC3: return 3;
		case DataType::DVEC4: return 4;

		case DataType::MAT2: return 2; // 2 vec2s
		case DataType::MAT3: return 3; // 3 vec3s
		case DataType::MAT4: return 4; // 4 vec4s
		}
	}
}
