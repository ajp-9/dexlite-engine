#pragma once

#include "../ShaderBase.hpp"

namespace dex
{
	namespace Shader
	{
		class Color3D : public Base
		{
		public:
			Color3D(const char* src = "assets/shaders/3d/color.glsl", const char* name = "ShaderColor")
				: Base(src, name)
			{}
		};
	}
}
