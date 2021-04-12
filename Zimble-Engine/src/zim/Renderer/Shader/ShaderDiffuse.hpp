#pragma once

#include "Shader.hpp"

namespace zim
{
	class ShaderDiffuse : public Shader
	{
	public:
		ShaderDiffuse(const char* src = "assets/shaders/diffuse3d.glsl", const char* name = "ShaderDiffuse")
			: Shader(src, name)
		{

		}

		void setSamplers()
		{
			setInt("u_TextureSampler", 0);
		}
	};
}
