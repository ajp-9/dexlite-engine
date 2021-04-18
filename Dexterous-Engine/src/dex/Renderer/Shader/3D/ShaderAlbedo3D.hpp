#pragma once

#include "../Shader.hpp"

namespace dex
{
	namespace Shader
	{
		class ShaderAlbedo3D : public Shader
		{
		public:
			ShaderAlbedo3D(const char* src = "assets/shaders/3d/albedo.glsl", const char* name = "ShaderDiffuse")
				: Shader(src, name)
			{}
		};
	}
}
