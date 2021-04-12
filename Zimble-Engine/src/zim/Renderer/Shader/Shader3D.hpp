#pragma once

#include "Shader.hpp"

namespace zim
{
	class Shader3D : public Shader
	{
	public:
		Shader3D(const char* src = "assets/shaders/3d.glsl", const char* name = "Shader3D");

		void setLocations3D();

		virtual void setProjectionViewMatrix(const glm::mat4& mat) override;
		virtual void setModelMatrix(const glm::mat4& mat) override;
	private:
		uint32_t u_ProjectionViewMatrix_Location = 0;
		uint32_t u_ModelMatrix_Location = 0;
	};
}
