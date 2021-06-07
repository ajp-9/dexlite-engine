#pragma once

#include "../ShaderBase.hpp"

namespace dex
{
	namespace Shader
	{
		class Default3D : public Base
		{
		public:
			Default3D(const char* src = "assets/shaders/3d/default.glsl");

			void setDiffuseMapEnabled(bool enabled);
			void setDiffuseMapSampler();

			void setSpecularMapEnabled(bool enabled);
			void setSpecularMapLocation();
		private:
			uint32 m_DiffuseMapSampler_Location = 0;
			uint32 m_DiffuseMapEnabled_Location = 0;

			uint32 m_SpecularMapSampler_Location = 0;
			uint32 m_SpecularMapEnabled_Location = 0;
		};
	}
}
