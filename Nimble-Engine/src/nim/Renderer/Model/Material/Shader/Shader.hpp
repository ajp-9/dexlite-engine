#pragma once

#include <string>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace nim
{
	class Shader
	{
	public:
		Shader(const char* src);
		~Shader();

		void bind() const;
		void unbind() const;

		void setMat4Uniform(const char* name, const glm::mat4& matrix);
	private:
		void checkShaderErrors(unsigned int shader, std::string type);
	private:
		uint32_t m_ID;
	};
}
