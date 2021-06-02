#pragma once

#include "../ShaderBase.hpp"

namespace dex
{
	namespace Shader
	{
		class Diffuse3D : public Base
		{
		public:
			Diffuse3D(const char* src = "assets/shaders/3d/diffuse.glsl", const char* name = "ShaderDiffuse")
				: Base(src, name)
			{}
		};
	}
}
