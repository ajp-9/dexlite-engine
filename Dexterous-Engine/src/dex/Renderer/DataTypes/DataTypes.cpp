#include "DataTypes.hpp"

#include <glad/glad.h>

namespace dex
{
	uint32 Data::getGLType(Type type)
	{
		switch (type)
		{
		case Type::BOOL: return GL_BOOL;

		case Type::CHAR: return GL_BYTE;

		case Type::INT: return GL_INT;
		case Type::IVEC2: return GL_INT;
		case Type::IVEC3: return GL_INT;
		case Type::IVEC4: return GL_INT;

		case Type::UINT: return GL_UNSIGNED_INT;
		case Type::UVEC2: return GL_UNSIGNED_INT;
		case Type::UVEC3: return GL_UNSIGNED_INT;
		case Type::UVEC4: return GL_UNSIGNED_INT;

		case Type::FLOAT: return GL_FLOAT;
		case Type::VEC2: return GL_FLOAT;
		case Type::VEC3: return GL_FLOAT;
		case Type::VEC4: return GL_FLOAT;

		case Type::DOUBLE: return GL_DOUBLE;
		case Type::DVEC2: return GL_DOUBLE;
		case Type::DVEC3: return GL_DOUBLE;
		case Type::DVEC4: return GL_DOUBLE;

		case Type::MAT2: return GL_FLOAT;
		case Type::MAT3: return GL_FLOAT;
		case Type::MAT4: return GL_FLOAT;

		default:
			std::cout << "Type::getGLType: Invalid Type\n";
			return 0;
		}
	}

	uint32 Data::getTypeSize(Type type)
	{
		switch (type)
		{
		case Type::BOOL: return sizeof(bool);

		case Type::CHAR: return sizeof(char);

		case Type::INT: return sizeof(int) * 1;
		case Type::IVEC2: return sizeof(int) * 2;
		case Type::IVEC3: return sizeof(int) * 3;
		case Type::IVEC4: return sizeof(int) * 4;

		case Type::UINT: return sizeof(unsigned int) * 1;
		case Type::UVEC2: return sizeof(unsigned int) * 2;
		case Type::UVEC3: return sizeof(unsigned int) * 3;
		case Type::UVEC4: return sizeof(unsigned int) * 4;

		case Type::FLOAT: return sizeof(float) * 1;
		case Type::VEC2: return sizeof(float) * 2;
		case Type::VEC3: return sizeof(float) * 3;
		case Type::VEC4: return sizeof(float) * 4;

		case Type::DOUBLE: return sizeof(double) * 1;
		case Type::DVEC2: return sizeof(double) * 2;
		case Type::DVEC3: return sizeof(double) * 3;
		case Type::DVEC4: return sizeof(double) * 4;

		case Type::MAT2: return sizeof(float) * 4;
		case Type::MAT3: return sizeof(float) * 9;
		case Type::MAT4: return sizeof(float) * 16;

		default:
			std::cout << "Type::getTypeSize: Invalid Type\n";
			return 0;
		}
	}

	uint32 Data::getTypeAmount(Type type)
	{
		switch (type)
		{
		case Type::BOOL: return 1;

		case Type::CHAR: return 1;

		case Type::INT: return 1;
		case Type::IVEC2: return 2;
		case Type::IVEC3: return 3;
		case Type::IVEC4: return 4;

		case Type::UINT: return 1;
		case Type::UVEC2: return 2;
		case Type::UVEC3: return 3;
		case Type::UVEC4: return 4;

		case Type::FLOAT: return 1;
		case Type::VEC2: return 2;
		case Type::VEC3: return 3;
		case Type::VEC4: return 4;

		case Type::DOUBLE: return 1;
		case Type::DVEC2: return 2;
		case Type::DVEC3: return 3;
		case Type::DVEC4: return 4;

		case Type::MAT2: return 2; // 2 vec2s
		case Type::MAT3: return 3; // 3 vec3s
		case Type::MAT4: return 4; // 4 vec4s

		default:
			std::cout << "Type::getTypeAmount: Invalid Type\n";
			return 0;
		}
	}

	uint32 Data::get_std140_BaseAlignment(Type type)
	{
		switch (type)
		{
		case Type::BOOL: return sizeof(uint32) * 1;

		case Type::CHAR: return sizeof(uint32) * 1;

		case Type::INT: return sizeof(int) * 1;
		case Type::IVEC2: return sizeof(int) * 2;
		case Type::IVEC3: return sizeof(int) * 4;
		case Type::IVEC4: return sizeof(int) * 4;

		case Type::UINT: return sizeof(unsigned int) * 1;
		case Type::UVEC2: return sizeof(unsigned int) * 2;
		case Type::UVEC3: return sizeof(unsigned int) * 4;
		case Type::UVEC4: return sizeof(unsigned int) * 4;

		case Type::FLOAT: return sizeof(float) * 1;
		case Type::VEC2: return sizeof(float) * 2;
		case Type::VEC3: return sizeof(float) * 4;
		case Type::VEC4: return sizeof(float) * 4;

		case Type::DOUBLE: return sizeof(double) * 1;
		case Type::DVEC2: return sizeof(double) * 2;
		case Type::DVEC3: return sizeof(double) * 4;
		case Type::DVEC4: return sizeof(double) * 4;

		case Type::MAT2: return sizeof(float) * 4;
		case Type::MAT3: return sizeof(float) * 16;
		case Type::MAT4: return sizeof(float) * 16;

		default:
			std::cout << "Type::getTypeSize: Invalid Type\n";
			return 0;
		}
	}
}
