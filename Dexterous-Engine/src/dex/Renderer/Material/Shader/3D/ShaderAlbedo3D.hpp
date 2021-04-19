#pragma once

#include "../ShaderBase.hpp"

namespace dex
{
	namespace Shader
	{
		class Albedo3D : public Base
		{
		public:
			Albedo3D(const char* src = "assets/shaders/3d/albedo.glsl", const char* name = "ShaderDiffuse")
				: Base(src, name)
			{}
		};
	}
}
