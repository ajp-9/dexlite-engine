#pragma once

#include "../ShaderBase.hpp"

namespace dex
{
	namespace Shader
	{
		class Default3D : public Base
		{
		public:
			Default3D(const char* src = "assets/shaders/3d/default.glsl", const char* name = "Default3D")
				: Base(src, name)
			{}

			void setSamplers()
			{
				setInt("u_TextureSampler", 0); //
			}
		};
	}
}
