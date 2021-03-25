#pragma once

#include <string>

namespace nim
{
	class Shader
	{
	public:
		Shader(const char* src);
		~Shader();

		void bind() const;
		void unbind() const;
	private:
		void checkShaderErrors(unsigned int shader, std::string type);
	private:
		uint32_t m_ID;
	};
}
