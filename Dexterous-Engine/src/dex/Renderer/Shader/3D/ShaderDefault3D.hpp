#pragma once

#include "../ShaderBase.hpp"

namespace dex
{
	namespace Shader
	{
		class Default3D : public Base
		{
		public:
			Default3D(const char* src = "assets/shaders/3d/texture.glsl")
				: Base(src, "Default3D", Type::DEFAULT_3D)
			{}

			void setSamplers()
			{
				setInt("u_TextureSampler", 0); //
			}
		};
	}
}
