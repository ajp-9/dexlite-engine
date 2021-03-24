#pragma once

#include <string>

namespace nim
{
	class Shader
	{
	public:
		Shader(const std::string& src);
		~Shader();

		void bind() const;
		void unbind() const;
	private:
		uint32_t m_ID;
	};
}
