#pragma once

#include "Shader3D.hpp"

namespace zim
{
	namespace Shader
	{
		class ShaderTexture3D : public Shader3D
		{
		public:
			ShaderTexture3D(const char* src = "assets/shaders/3d/texture.glsl", const char* name = "ShaderTexture3D")
				: Shader3D(src, name)
			{
				setSamplers();
			}

			void setSamplers()
			{
				setInt("u_TextureSampler", 0);
			}
		};
	}
}
